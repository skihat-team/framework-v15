<?php
/**
 * routing.inc 提供MVC路由配置声明。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.boots
 * @version   1.5
 *
 * @created   2012-07-22
 * @modified  2015-04-07
 */

Router::domain(SKIHAT_CURRENT_DOMAIN)
    ->rule(array(SKIHAT_IOC_CLASS => '#NormalRouterRule',
        SKIHAT_PARAM_CONTROLLER => SKIHAT_PARAM_DEFAULT_CONTROLLER,
        SKIHAT_PARAM_ACTION => SKIHAT_PARAM_DEFAULT_ACTION
    ));