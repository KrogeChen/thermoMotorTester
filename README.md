# thermoMotorTester

热马达综合测试仪

## 功能介绍

- 测试热马达的行程、温度、负载力、功率、电压、电流
- 系统电压DC12-24V
- 测试电压AC12、AC24V、AC36V、AC110、AC220V
- 需要配置PC端软件，记录参数的曲线
- 能够长期运行对产品进行老化

## 系统组成 

- 主控板、继电器输出板、测力仪、电参数测量仪、温控仪、变压器、PC软件

## 器件选型

* [MCU:STM32F103RCT6](https://github.com/KrogeChen/thermoMotorTester/tree/master/document/STM32F103) 
* [继电器:HF115-005-2ZS](https://github.com/KrogeChen/thermoMotorTester/tree/master/document/HF115F_005-2ZS4AF) 
* [电参:PM9808](https://github.com/KrogeChen/thermoMotorTester/tree/master/document/PM9808) 
* [温控仪:](https://github.com/Microsoft/vscode/wiki/How-to-Contribute#debugging) 

## 设计说明

- 设备电压:AC220V 
- 主板实现电压的转换、测量数据的采集
- 测试电压输出采用继电器触点互锁的方式、任何时候只允许输出一组电压。
- 设计7个输入点、7个输出点
- 5组UART通讯(2组RS323、1组RS485、1组TTL、1组BGH)
- 主要协议modbus RTU 主机，bough