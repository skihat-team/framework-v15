<?php
/**
 * index_controller.inc 配置文件声明。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   app.boots
 * @version   1.5
 *
 * @created   2012-08-07
 * @modified  2015-04-07
 */

# 写入缓存配置信息。
Skihat::write('kernels/caches', array(
    'default' => array(
        SKIHAT_IOC_CLASS => 'kernels.caches.engines.file_cache_engine',
        SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
        'paths' => SKIHAT_PATH_DATA_CACHES),
    'runtime' => array(
        SKIHAT_IOC_CLASS => 'kernels.caches.engines.file_cache_engine',
        SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
        'paths' => SKIHAT_PATH_DATA_RUNTIME,
        'prefix' => 'runtime')
));

# 写入数据库配置信息。
Skihat::write('kernels/databases', array(
    'default' => array(
        SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
        SKIHAT_IOC_CLASS => 'kernels.databases.engines.mysql-pdo-engine',
        'conf' => 'mysql:host=127.0.0.1;dbname=6vtao&user=root&pass=123321&charset=utf8'
        #'conf' => 'mysql:host=qdm-046.hichina.com;dbname=qdm0460720_db&user=qdm0460720&pass=thp20141011&charset=utf8'
    )
));

# 写入资源管理配置信息。
Skihat::write('kernels/medias', array(
    'default' => array(
        SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
        SKIHAT_IOC_CLASS => 'kernels.medias.engines.file-media-engine'
    )
));

# 设置安全信息。
/*
Skihat::write('kernels/securities', array(
    'authentications' => array(
        'acenter' => array(
            SKIHAT_IOC_PATHS => SKIHAT_PATH_APP_MODULES,
            SKIHAT_IOC_CLASS => 'acenter.extends.acenter_authentication'
        ),
        'ucenter' => array(
            SKIHAT_IOC_PATHS => SKIHAT_PATH_APP_MODULES,
            SKIHAT_IOC_CLASS => 'ucenter.extends.ucenter_authentication'
        )
    ),
    'authorizations' => array()
));
*/