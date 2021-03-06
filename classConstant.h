#ifndef CLASSCONSTANT_H
#define CLASSCONSTANT_H
// 宏定义以及类与结构体的定义
//#include <QtCore>
//#include <QtGui>
#include <QtWidgets>
#include <QMessageBox>
#include <QDebug>   // Qt Debug
//#include <QHostAddress>
/// 服务器端 ServerNode 节点类
enum STATUS{    // 状态
    OFFLINE = 0,    // 离线 = 0
    ONLINE = 1,     // 在线 = 1
    TIMEOUT = 2     // 连接超时 = 2
};
enum REQUEST{   // 请求
    LOGIN = 10,     // 登录 = 10
    QUERY = 11,     // 查找 = 11
    LOGOUT = 12,    // 登出 = 12
    MESSAGE = 13    // 发送信息 = 13
};
enum REPLY{     // 回复
    NO_REPLY = 99,          // 无回复
    // 登录回复
    LOGIN_SUCCESS = 20,     // 登录成功 = 20
    LOGIN_NO_ACCOUNT = 21,  // 用户名格式错误
    LOGIN_WRONG_INPUT = 22, // 用户名或密码错误
    HAVE_LOGINED = 23,        // 已经登录
    // 查找好友回复
    FRIEND_OFFLINE = 25,    // 好友未在线
    FRIEND_NO_ACCOUNT = 27, // 无此账号
    FRIEND_ONLINE = 26,     // 好友在线
    // 登出回复
    LOGOUT_SUCCESS = 30,    // 登出成功
    LOGOUT_FAILED = 31,      // 登出失败
    // 会话消息回复
    NO_MESSAGE = 40,        // 无消息
    NAVE_MESSAGE = 41,      // 有消息
    HAVE_TALK_MESSAGE = 42  // 有会消息

};

/// 全局变量
const QRegExp ipRegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");       // 判断 IP 地址正则表达式
// QRegExp ipRegExp("\\b((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.)""{3}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))\\b");    // 判断 IP 地址正则表达式
const QRegExp portRegExp("(/^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)/)");    // 判断端口号正则表达式
const QRegExp macRegExp("([0-9A-F]{2}-[0-9A-F]{2}-[0-9A-F]{2}-[0-9A-F]{2}-[0-9A-F]{2}-[0-9A-F]{2})");    // 判断 MAC 地址正则表达式

/// 结构体定义
struct ServerNode{
    QString hostAddr;       // 服务器地址
    quint16 hostPort;       // 服务器端口
    ServerNode()
    {
        hostPort = 0; /*  */
    }
};
// 用户信息类
struct UserInfo{
    QString account;        // 账号
    QString password;       // 密码
    QString nickname;       // 昵称
    int avatarNumber;       // 头像编号
    int status;              // 登录状态
    QString mobileNumber;   // 手机号码
    QString phoneNumber;    // 电话号码
    QString birthday;       // 生日
    QString city;           // 城市
    QString aboutMyself;    // 个人描述
    UserInfo()
    {
        avatarNumber = 0;
        status =  0;
    }
    //重载输入输出操作符
    friend QDataStream & operator<< (QDataStream &qos, const UserInfo &pi)
    {
        qos << pi.account << pi.password << pi.nickname << pi.avatarNumber
            << pi.status << pi.mobileNumber
            << pi.phoneNumber << pi.birthday<< pi.city << pi.aboutMyself;
        return qos;
    }
    friend QDataStream & operator>> (QDataStream &qis, UserInfo &pi)
    {
        qis >> pi.account >> pi.password >> pi.nickname >> pi.avatarNumber
            >> pi.status >> pi.mobileNumber
            >> pi.phoneNumber >> pi.birthday >> pi.city >> pi.aboutMyself;
        return qis;
    }

};
// 用户登录信息类
struct LoginInfo{
    QString account;
    QString password;
    int status;
    LoginInfo()
    {
        status = 0;
    }
    friend QDataStream & operator<< (QDataStream &qos, LoginInfo &li)
    {
        qos << li.account << li.password << li.status;
        return qos;
    }
    friend QDataStream & operator>> (QDataStream &qis, LoginInfo &li)
    {
        qis >> li.account >> li.password >> li.status;
        return qis;
    }
};
// 好友信息类
struct FriendInfo
{
    QString account;        // 好友账号
    ServerNode node;        // 好友IP地址节点
    QString name;           // 好友名字
    int avatarNumber;       // 好友头像编号
    int status;             // 好友在线状态
    QString about;          // 好友信息
    int friendKind;        //好友类型
    QString remark;			//好友备注

    FriendInfo()
    {	avatarNumber = status = friendKind = 0;	}

    friend QDataStream & operator<< (QDataStream &qos, const FriendInfo &fi)
    {
        qos << fi.account << fi.name << fi.avatarNumber << fi.status
            << fi.about << fi.friendKind << fi.remark;
        return qos;
    }
    friend QDataStream & operator>> (QDataStream &qis, FriendInfo &fi)
    {
        qis >> fi.account >> fi.name >> fi.avatarNumber >> fi.status
            >> fi.about >> fi.friendKind >> fi.remark;
        return qis;
    }
};
// 会话消息类
struct Message
{
    int kind;				//消息类型
    QString sender;			//发送者
    QString receiver;		//接收者
    QString text;			//消息内容

    Message()
    {	kind = 0;	}
    friend QDataStream & operator<< (QDataStream &qos, const Message &mes)
    {
        qos << mes.kind << mes.sender << mes.receiver << mes.text;
        return qos;
    }
    friend QDataStream & operator>> (QDataStream &qis, Message &mes)
    {
        qis >> mes.kind >> mes.sender >> mes.receiver >> mes.text;
        return qis;
    }
};

#endif // CLASSCONSTANT_H
