<?php
/**
 * index.php 应用入口文件，提供应用的入口。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.publics
 * @version   1.5
 *
 * @created   2012-07-23
 * @modified  2015-04-07
 */

# 导入启动核心文件。
require(dirname(dirname(__FILE__)) . '/boots/startup.inc');

# 开启前端控制器，并初始化和分发控制器。
$app = new Application();
$app->initialize();
$app->dispatching();