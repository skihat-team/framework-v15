<?php
/**
 * cache-filter.inc 提供活动缓存过滤器声明。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.controllers.filters
 * @version   1.5
 *
 * @created   2013-04-08
 * @modified  2015-04-07
 */

/**
 * 缓存过滤器，提供控制器活动的缓存支持。
 *
 * @package skihat.controllers.filters
 */
class CacheFilter implements IActionFilter {
    /**
     * @var array 允许进行缓存的活动方法名称。
     */
    public $actionMethods = array();

    /**
     * @var string 使用的缓存引擎。
     */
    public $engine = 'default';

    /**
     * @var int 缓存有效时间（秒）。
     */
    public $expire = 3600;

    /**
     * @see IActionFilter::initialize
     */
    public function initialize(Controller $controller) {
        $this->_controller = $controller;
    }

    /**
     * @see IActionFilter::invoke
     */
    public function invoke($actionMethod) {
        # 如果不允许缓存，直接返回。
        if (!$this->_enableCached($actionMethod)) return true;

        # 根据活动设置活动的缓存名称。
        $this->_actionCacheName = $this->_cacheName($actionMethod);
        # 如果读取缓存成功，则将缓存值写入到响应实例中。
        if ($cache = Cache::read($this->_actionCacheName, $this->engine)) {
            $this->_controller->response->copy($cache);
            return false;
        }

        $this->_enableCache = true;
        return true;
    }

    /**
     * @see IActionFilter::render
     */
    public function render(array &$options) {
        return true;
    }

    /**
     * @see IActionFilter::complete
     */
    public function complete() {
        if ($this->_enableCache) {
            Cache::write(
                $this->_actionCacheName,
                $this->_controller->response,
                $this->engine, $this->expire
            );
        }
    }

    /**
     * 根据$actionMethod返回一个布尔值，表示是否允许进行缓存。
     *
     * @param string $actionMethod 活动名称。
     *
     * @return bool
     */
    protected function _enableCached($actionMethod) {
        # 如果当前不开启缓存或请求方法不为GET请求。
        if (!$this->_enableCachedEnv()) return false;
        if (!$this->actionMethods) return false;
        if ($this->actionMethods == '*') return true;

        # 返回允许缓存当前方法，并且当前方法的允许值为非空值。
        return isset($this->actionMethods[$actionMethod])
        && $this->actionMethods[$actionMethod] !== false;
    }

    /**
     * 返回一个布尔值，表示缓存的环境限制。
     *
     * @return bool
     */
    protected function _enableCachedEnv() {
        return enable_cached() && (client_method() == 'get');
    }

    /**
     * 返回当前请求的缓存名称。
     *
     * @param string $actionMethod 缓存方法。
     *
     * @return string
     */
    function _cacheName($actionMethod) {
        # 获取当前请求，并且生成完整内容。
        $request = $this->_controller->request;
        $all = $request->queryAll();

        # 如果活动方法是全部，则直接返回请求数组生成的结果。
        if ($this->actionMethods == '*' || $this->actionMethods[$actionMethod] === true) {
            return 'cache-filter-' . implode('-', array_keys($all)) . '-' . implode('-', $all);
        }

        # 生成默认参数集。
        $params = array(
            SKIHAT_PARAM_MODULE => $request->module(),
            SKIHAT_PARAM_PACKAGE => $request->package(),
            SKIHAT_PARAM_CONTROLLER => $request->controller(),
            SKIHAT_PARAM_ACTION => $request->action(),
            SKIHAT_PARAM_ID => $request->query(SKIHAT_PARAM_ID),
            SKIHAT_PARAM_FMT => $request->fmt()
        );
        # 附加自定义参数集。
        foreach ((array)$this->actionMethods[$actionMethod] as $param) {
            $params[$param] = $request->query($param);
        }

        return 'cache-filter-' . implode('-', array_keys($params)) . '-' . implode('-', $params);
    }

    /**
     * @var Controller 控制器。
     */
    protected $_controller = null;

    /**
     * @var bool 是否开启缓存。
     */
    protected $_enableCache = false;

    /**
     * @var bool|string 当前的缓存方法。
     */
    protected $_actionCacheName = false;
}

