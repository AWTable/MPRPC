#include<iostream>
#include<string>
#include"../user.pb.h"
#include"mprpcapplication.h"
#include"rpcprovider.h"
using namespace fixbug;

class UserService:public fixbug::UserServiceRpc
{
public:
    bool Login(std::string name,std::string pwd)
    {
        std::cout<<"doing local service :Login"<<std::endl;
        std::cout<<"name:"<<name<<"pwd:"<<pwd<<std::endl;
        return true;
    }

    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)

    {
        //框架给业务上报了请求参数loginRequest  应用获取相应数据做本地业务
        std::string name=request->name();
        std::string pwd=request->pwd();

        //做本地业务
        bool login_result=Login(name,pwd);

        //把相应写入    包括错误码，错误信息，返回值
        fixbug::ResultCode *code=response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        //执行回调操作  执行响应对象数据的序列化和网络发送（都是由框架来完成的）
        done->Run();
    }
};

int main(int argc,char *argv[])
{
    //调用框架的初始化操作
    MprpcApplication::Init(argc,argv);

    //provider是一个rpc网络服务对象，把userservice对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    //启动一个rpc服务发布节点   run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();
    return 0;
}