<?php
/**
 * application.inc 提供MVC前端应用控制器声明。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.appservs
 * @version   1.5
 *
 * @created   2014-12-01
 * @modified  2015-04-07
 */

# 引用应用基础类。
Skihat::import('applications.application-base', SKIHAT_PATH_LIBRARY);

/**
 * 应用前端控制器类，处理应用请求可关服务。
 *
 * @package skihat.appservs
 */
class Application extends ApplicationBase {
    /**
     * @see ApplicationBase._initializeConfig
     */
    protected function _initializeConfig() {
        // 加载
        parent::_initializeConfig();

        // 加载应用配置信息。

    }
}