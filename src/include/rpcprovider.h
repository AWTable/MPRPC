#pragma once
#include"google/protobuf/service.h"
#include<memory>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/InetAddress.h>
#include<muduo/net/TcpConnection.h>
#include<unordered_map>
#include<google/protobuf/descriptor.h>

//框架提供的专门服务发布rpc服务的网络对象类
class RpcProvider
{
public:
    //这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    //启动rpc
    void Run();
private:
    muduo::net::EventLoop m_eventLoop;

    struct ServiceInfo
    {
        google::protobuf::Service *m_service;//保存服务对象

        //保存服务方法
        std::unordered_map<std::string,const google::protobuf::MethodDescriptorProto*> m_methodMap;
    };
    //储存注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string,ServiceInfo> m_serviceMap;

    void OnConnection(const muduo::net::TcpConnectionPtr&);

    void OnMessage(const muduo::net::TcpConnectionPtr&,
                            muduo::net::Buffer*,
                            muduo::Timestamp);

    void SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message *response);
};