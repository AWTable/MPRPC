#include"test.pb.h"
#include<iostream>
#include<string>

using namespace fixbug;


int main()
{
    // LoginResponse rsp;
    // ResultCode *rc=rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登录处理失败了");

    GetFriendListsResponse rsp;
    ResultCode *rc=rsp.mutable_result();
    rc->set_errcode(0);

    User *user1=rsp.add_friend_list();
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2=rsp.add_friend_list();
    user2->set_name("zhang san");
    user2->set_age(20);
    user2->set_sex(User::MAN);

    std::cout<<rsp.friend_list_size()<<std::endl;
}
// int main()
// {

//     LoginRequest req;
//     req.set_name("zhang san");
//     req.set_pwd("123456");

//     std::string send_str;
//     if(req.SerializeToString(&send_str))
//     {
//         std::cout<<send_str.c_str()<<std::endl;
//     }
//     return 0;
// }