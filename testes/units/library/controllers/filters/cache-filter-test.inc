<?php
/**
 * cache-filter-test.inc 提供缓存过滤器的单元测试服务。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.controllers.filters
 * @version   1.5
 *
 * @created   2012-07-22
 * @modified  2015-04-07
 */

# 引用测试启动文件。
require_once(dirname(dirname(dirname(dirname(__FILE__)))) . '/startup.inc');

# 引用被测试类.
Skihat::import('kernels.caches.cache', SKIHAT_PATH_LIBRARY);
Skihat::import('applications.application-request', SKIHAT_PATH_LIBRARY);
Skihat::import('applications.application-response', SKIHAT_PATH_LIBRARY);

Skihat::import('controllers.controller', SKIHAT_PATH_LIBRARY);
Skihat::import('controllers.filters.cache-filter', SKIHAT_PATH_LIBRARY);

/**
 * 缓存过滤器测试，提供缓存过滤的单元测试服务。
 *
 * @package skihat.controllers.filters
 */
class CacheFilterTest extends PHPUnit_Framework_TestCase {
    # @see PHPUnit_Framework_TestCase::setUp
    public function setUp() {
        Skihat::write('kernels/caches', array(
            'default' => '#CacheFilterCacheEngine'
        ));

        Cache::initialize();
        CacheFilterCacheEngine::reset();
    }

    /**
     * 测试默认执行。
     */
    public function testDefaultConstruct() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array());
        $controller = new CacheFilterController(
            array('cacheFilter' => '#CacheFilterMock')
        );

        $controller->invoke($request, $response);
        $this->assertEmpty(CacheFilterCacheEngine::$caches);
    }

    /**
     * 测试招待全部方法。
     */
    public function testActionMethodAll() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => '*'
            ))
        );
        $controller->invoke($request, $response);

        $this->assertEquals(1, count(CacheFilterCacheEngine::$caches));
        $this->assertArrayHasKey('cache-filter-action-index', CacheFilterCacheEngine::$caches);
    }

    /**
     * 测试活动方法允许缓存。
     */
    public function testActionMethodAllow() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index', 'custom' => 2));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => true)
            ))
        );
        $controller->invoke($request, $response);

        $this->assertEquals(1, count(CacheFilterCacheEngine::$caches));
        $this->assertArrayHasKey('cache-filter-action-custom-index-2', CacheFilterCacheEngine::$caches);
    }

    /**
     * 测试活动方法允许缓存，指定缓存参数数组。
     */
    public function testActionMethodAllowForArray() {
        $request = $this->createRequest(array('action' => 'index'));
        $response = new ApplicationResponse();
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => array('id'))
            ))
        );
        $controller->invoke($request, $response);

        $this->assertEquals(1, count(CacheFilterCacheEngine::$caches));
        $this->assertArrayHasKey('cache-filter-module-package-controller-action-id-fmt---index-index--html', CacheFilterCacheEngine::$caches);
    }

    /**
     * 测试活动方法允许缓存，指定缓存参数数组。
     */
    public function testActionMethodAllowForArrayParams() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index', 'key' => 'abc', 'custom' => 'edd'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => array('key'))
            ))
        );
        $controller->invoke($request, $response);
        $this->assertEquals(1, count(CacheFilterCacheEngine::$caches));
        $this->assertArrayHasKey('cache-filter-module-package-controller-action-id-fmt-key---index-index--html-abc', CacheFilterCacheEngine::$caches);
    }

    /**
     * 测试活动方法缓存失败，指定空值。
     */
    public function testActionMethodAllowForEmptyArray() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => array())
            ))
        );

        $controller->invoke($request, $response);
        $this->assertEquals(1, count(CacheFilterCacheEngine::$caches));
        $this->assertArrayHasKey('cache-filter-module-package-controller-action-id-fmt---index-index--html', CacheFilterCacheEngine::$caches);
    }


    /**
     * 测试活动方法不允许缓存。
     */
    public function testActionMethodDeny() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'edit'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => true)
            ))
        );
        $controller->invoke($request, $response);

        $this->assertEquals(0, count(CacheFilterCacheEngine::$caches));
    }

    /**
     * 测试活动方法缓存，指定的内容为字符串
     */
    public function testActionMethodDenyForString() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => 'indexAction'
            ))
        );
        $controller->invoke($request, $response);

        $this->assertEquals(0, count(CacheFilterCacheEngine::$caches));
    }

    /**
     * 测试活动方法缓存失败，指定False值。
     */
    public function testActionMethodDenyForFalse() {
        $response = new ApplicationResponse();
        $request = $this->createRequest(array('action' => 'index'));
        $controller = new CacheFilterController(
            array('cacheFilter' => array(
                SKIHAT_IOC_CLASS => '#CacheFilterMock',
                'actionMethods' => array('indexAction' => false)
            ))
        );
        $controller->invoke($request, $response);
        $this->assertEquals(0, count(CacheFilterCacheEngine::$caches));
    }

    # 根据$params创建请求参数。
    protected function createRequest($params) {
        $request = new ApplicationRequest();
        $request->initialize($params);

        return $request;
    }

}

/**
 * 缓存过滤器模拟器，提供缓存过滤的模拟服务。
 *
 * @package skihat.controllers.filters
 */
class CacheFilterMock extends CacheFilter {
    protected function _enableCachedEnv() {
        return true;
    }
}

/**
 * 缓存过滤器引擎模拟器。
 *
 * @package skihat.controllers.filters
 */
class CacheFilterCacheEngine implements ICacheEngine {
    public static $caches = array();

    public static function reset() {
        self::$caches = array();
    }

    # @see ICacheEngine::write
    function write($name, $value, $expire = Cache::DEFAULT_EXPIRE) {
        self::$caches[$name] = $value;
    }

    # @see ICacheEngine::read
    function read($name) {
        return isset(self::$caches[$name]) ? self::$caches[$name] : false;
    }

    # @see ICacheEngine::delete
    function delete($name) {
        unset(self::$caches[$name]);
    }

    # @see ICacheEngine::flush
    public function flush() {
        self::$caches = array();
    }
}

/**
 * 缓存过滤模拟控制器。
 *
 * @package skihat.controllers.filters
 */
class CacheFilterController extends Controller {
    # 使用$filters控制器。
    public function __construct($filters = array()) {
        $this->_filters = $filters;
        $this->autoRender = false;
    }

    public function indexAction() {
        $this->text('index');
    }

    public function editAction() {
        $this->text('edit');
    }

    public function actionFilters() {
        return $this->_filters;
    }

    # 过滤器方法。
    protected $_filters = array();
}