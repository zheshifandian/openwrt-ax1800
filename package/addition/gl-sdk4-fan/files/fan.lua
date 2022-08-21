--[[
    @object-name: fan
    @object-desc: This is the API related to fan Internet access.
--]]

local utils = require "oui.utils"

local M = {}
 
local function stop_test_fan()
    utils.writefile("/sys/class/thermal/cooling_device0/cur_state", "0")
    ngx.pipe.spawn({"/etc/init.d/gl_fan", "restart"}):wait()
end

--[[
    @method-name: set_status
    @method-desc: Set led status.

    @in bool     test_fan              测试风扇起转.
    @in number   test_time             测试风扇起转时间s, 缺省为10s.
    @in-example:  {\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":[\"\",\"fan\",\"set_status\",{\"test_fan\":true,\"test_time\":5}],\"id\":1}
    @out-example: {\"jsonrpc\": \"2.0\", \"id\": 1, \"result\": {}}
--]]

M.set_status = function(params)

    local test_fan = params.test_fan
    if test_fan == true then
        local test_time = params.test_time or 10
        ngx.pipe.spawn({"/etc/init.d/gl_fan", "stop"}):wait()
        utils.writefile("/sys/class/thermal/cooling_device0/cur_state", "255")
        ngx.timer.at(test_time, stop_test_fan)
    end
    
end
 
--[[
    @method-name: get_status
    @method-desc: Get status of fan.

    @in  bool     get_speed             是否获取风扇转速，true:是 false 否.
    @out number   fan_speed             风扇转速.
    @out bool     fan_status            风扇状态，true:开启 false:关闭.

    @in-example:  {\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":[\"\",\"fan\",\"get_status\",{\"get_speed\":true}],\"id\":1}
    @out-example: {"id":1,"jsonrpc":"2.0","result":{"fan_speed":2000,"fan_status":true}}
--]]
M.get_status = function(params)

    local res = {}
    local get_speed = params.get_speed
    if get_speed == true then
        utils.writefile("/sys/class/fan/fan_speed", "refresh")
        ngx.sleep(1.5)
        res.fan_speed = tonumber(utils.readfile("/sys/class/fan/fan_speed"):match("(%d+)"))
    end

    res.status = tonumber(utils.readfile("/sys/class/thermal/cooling_device0/cur_state", 'n') or 0) ~= 0 and true or false

    return res
end

return M
