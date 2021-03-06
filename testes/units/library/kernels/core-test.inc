<?php
/**
 * core-test.inc 提供Skihat核心方法单元测试服务。
 *
 * @copyright 2012-2015 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   skihat.kernels
 * @version   1.5
 *
 * @created   2012-06-12
 * @modified  2015-04-05
 */

# 引用测试启动文件。
require_once(dirname(dirname(dirname(__FILE__))) . '/startup.inc');

/**
 * CoreTest 核心方法单元测试类，提供核心方法的单元测试服务。
 *
 * @package skihat.kernels
 */
class CoreTest extends PHPUnit_Framework_TestCase {
    /**
     * camel大写命名规范，测试方法。
     */
    public function testCamelUpper() {
        $this->assertEquals('helloWorld', camel_upper('HelloWorld'));

        $this->assertEquals('helloWorld', camel_upper('hello_world'));
        $this->assertEquals('helloWorld', camel_upper('_hello_world'));

        $this->assertEquals('helloWorld', camel_upper('hello-world'));
        $this->assertEquals('helloWorld', camel_upper('-hello-world'));
    }

    /**
     * camel小写命名规范，测试方法。
     */
    public function testCamelLower() {
        $this->assertEquals('hello_world', camel_lower('helloWorld'));
        $this->assertEquals('hello_world', camel_lower('HelloWorld'));

        $this->assertEquals('hello_world', camel_lower('hello-world'));
        $this->assertEquals('hello_world', camel_lower('-hello-world'));
    }

    /**
     * camel中线命名规则，测试方法。
     */
    public function testCamelLine() {
        $this->assertEquals('hello-world', camel_line('helloWorld'));
        $this->assertEquals('hello-world', camel_line('HelloWorld'));

        $this->assertEquals('hello-world', camel_line('hello_world'));
        $this->assertEquals('hello-world', camel_line('_hello_world'));
    }

    /**
     * pascal命名规范，测试方法。
     */
    public function testPascal() {
        $this->assertEquals('HelloWorld', pascal('helloWorld'));

        $this->assertEquals('HelloWorld', pascal('hello_world'));
        $this->assertEquals('HelloWorld', pascal('_hello_world'));

        $this->assertEquals('HelloWorld', pascal('hello-world'));
        $this->assertEquals('HelloWorld', pascal('-hello-world'));
    }

    /**
     * array_key_value 单元测试。
     */
    public function testArrayKeyValue() {
        $array = array('name' => 'example', 'title' => 'hello');

        $this->assertEquals('example', array_key_value($array, 'name'));
        $this->assertEquals('hello', array_key_value($array, 'title'));
    }

    /**
     * array_key_value 单元测试，默认值。
     */
    public function testArrayKeyValueForDefault() {
        $array = array();

        $this->assertEquals('world', array_key_value($array, 'name', 'world'));
        $this->assertFalse(array_key_value($array, 'name'));
    }

    /**
     * array_key_pop 单元测试。
     */
    public function testArrayKeyPop() {
        $array = array('name' => 'example');

        $this->assertEquals('example', array_key_pop($array, 'name'));
        $this->assertEmpty($array);
    }

    /**
     * array_key_pop 单元测试，索引值不存在。
     */
    public function testArrayKeyPopForDefault() {
        $array = array();
        $this->assertEquals('default', array_key_pop($array, 'name', 'default'));
        $this->assertFalse(array_key_pop($array, 'name'));
    }

    /**
     * 执行数组主键过滤。
     */
    public function testArrayKeyFilter() {
        $array = array(2 => 'tow', 3 => 'three', 'f' => 4);
        $array = array_key_filter($array, 'is_numeric');

        $this->assertEquals(2, count($array));
        $this->assertEquals('tow', $array[2]);
        $this->assertEquals('three', $array[3]);
    }

    /**
     * 测试数组连接字符串。
     */
    public function testArrayJoin() {
        $array = array('class' => 'default');

        array_join_str($array, 'class', ' primary');
        array_join_str($array, 'id', 'obj');

        $this->assertEquals(2, count($array));
        $this->assertEquals('default primary', $array['class']);
        $this->assertEquals('obj', $array['id']);
    }
}