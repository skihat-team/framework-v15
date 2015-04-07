<?php
/**
 * all-test.inc 提供SkiHat框架全部单元测试服务。
 *
 * @copyright 2012-2015 SkiHat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    SkiHat Team
 *
 * @package   skihat
 * @version   1.5
 *
 * @created   2012-08-12
 * @modified  2015-04-05
 */

# 引用启动文件。
require_once(dirname(__FILE__) . '/startup.inc');

/**
 * 全部测试，提供架构完整测试服务支持。
 *
 * @package skihat
 */
class AllTest extends PHPUnit_Framework_TestSuite {
    /**
     * @see PHPUnit_Framework_testSukit
     */
    public static function suite() {
        $all = new AllTest('all');

        # 测试内核文件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/core-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/coll-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/iocfa-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/skihat-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/validators-test.inc');

        # 测试缓存组件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/caches/cache-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/caches/engines/file-cache-engine-test.inc');

        # 测试日志组件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/loggers/logger-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/loggers/engines/file-logger-engine-test.inc');

        # 富媒体组件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/medias/media-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/medias/engines/file-media-engine-test.inc');

        # 安全组合件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/securities/security-test.inc');

        # 事务组件。
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/transactions/transaction-test.inc');

        # 数据库组件
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/databases/database-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/databases/sql-builder-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/kernels/databases/engines/mysql-pdo-engine-test.inc');

        # 应用前端组件
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/applications/application-base-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/applications/application-request-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/applications/application-response-test.inc');

        # 控制器组件
        #  $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/controllers/controller_test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/controllers/action-filters-test.inc');

        # 模型组件
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/models/model-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/models/model-fetch-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/models/model-meta-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/models/model-links-test.inc');

        # 路由组件
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/routers/router-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/routers/router-rules-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/routers/router-styles-test.inc');

        # 视图组件
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/views/theme-test.inc');
        $all->addTestFile(SKIHAT_PATH_TESTES_UNITS . '/library/views/__helpers/form-test.inc');

        return $all;
    }
}