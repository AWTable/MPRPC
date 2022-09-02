```
./autobuild.sh    //运行脚本
```

# ·    项目简介

    基于protobuf的分布式网络通讯框架

    利用了zookeeper的服务注册中心

# ·    环境配置

##        项目代码工程目录

            bin：可执行文件
            build：项目编译文件
            lib：项目库文件
            src：源文件
            test：测试代码
            example：框架代码使用范例
            CMakeLists.txt：顶层的cmake文件
            README.md：项目自述文件
            autobuild.sh：一键编译脚本

##         第三方库

            protobuf        

            muduo网络库

            zookeeper分布式协调服务

# 项目主要类描述

## class MprpcConfig

```
 //读取配置文件，并保存在map表中
 class MprpcConfig
 
 // 负责解析加载配置文件
 void LoadConfigFile(const char *config_file);
 
 // 查询配置项信息
 std::string Load(const std::string &key);
```

## class MprpcApplication

```
// mprpc框架的基础类，负责框架的一些初始化操作

class MprpcApplication
     static void Init(int argc, char **argv);
     static MprpcApplication& GetInstance();
     static MprpcConfig& GetConfig();

     static MprpcConfig m_config;
```

## class RpcProvider

```
// 框架提供的专门发布rpc服务的网络对象类

class RpcProvider
 // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
 void NotifyService(google::protobuf::Service *service);

     // 启动rpc服务节点并向zookeeper上注册信息，开始提供rpc远程网络调用服务
 void Run();

    // service服务类型信息
 struct ServiceInfo
 {
 google::protobuf::Service *m_service; // 保存服务对象
 std::unordered_map<std::string, const google::protobuf::MethodDescriptor*>         m_methodMap; // 保存服务方法
 };
 // 存储注册成功的服务对象和其服务方法的所有信息
 std::unordered_map<std::string, ServiceInfo> m_serviceMap;
```

## muduo绑定的消息回调函数OnMessage

```

  // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
  // new UserService().Login(controller, request, response, done)
  service->CallMethod(method, nullptr, request, response, done);


  //序列化数据并发送数据
重写基类方法中done->Run() --》void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn,     google::protobuf::Message *response)

    
```

## mprpc的调用

```

fixbug::FiendServiceRpc_Stub stub(new MprpcChannel());

stub.GetFriendsList(&controller, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

//数据格式
//header_size + service_name method_name args_size + args

```

