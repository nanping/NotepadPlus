#ifndef DEF_PARAMETERS_H
#define DEF_PARAMETERS_H

#define  EXTAND_ARGS(args) args //__VA_ARGS__在vs中会被认为是一个实参，所以需要定义该宏过度
#define CONCATENATE(arg1, arg2)  arg1##arg2

// 计算 __VA_ARGS__ 参数个数,最大支持64个参数 //vs中无参数时会返回1
#define FL_ARG_COUNT(...) EXTAND_ARGS(FL_INTERNAL_ARG_COUNT_PRIVATE(0, __VA_ARGS__,\
    64, 63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
    9,  8,  7,  6,  5,  4,  3,  2,  1,  0))
#define FL_INTERNAL_ARG_COUNT_PRIVATE(\
    _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64, N, ...) N


#define EXTEND_1(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,1)
#define EXTEND_2(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,2)  EXTAND_ARGS(EXTEND_1(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_3(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,3)  EXTAND_ARGS(EXTEND_2(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_4(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,4)  EXTAND_ARGS(EXTEND_3(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_5(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,5)  EXTAND_ARGS(EXTEND_4(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_6(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,6)  EXTAND_ARGS(EXTEND_5(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_7(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,7)  EXTAND_ARGS(EXTEND_6(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_8(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,8)  EXTAND_ARGS(EXTEND_7(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_9(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,9)  EXTAND_ARGS(EXTEND_8(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_10(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,10)  EXTAND_ARGS(EXTEND_9(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_11(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,11)  EXTAND_ARGS(EXTEND_10(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_12(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,12)  EXTAND_ARGS(EXTEND_11(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_13(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,13)  EXTAND_ARGS(EXTEND_12(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_14(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,14)  EXTAND_ARGS(EXTEND_13(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_15(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,15)  EXTAND_ARGS(EXTEND_14(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_16(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,16)  EXTAND_ARGS(EXTEND_15(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_17(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,17)  EXTAND_ARGS(EXTEND_16(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_18(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,18)  EXTAND_ARGS(EXTEND_17(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_19(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,19)  EXTAND_ARGS(EXTEND_18(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_20(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,20)  EXTAND_ARGS(EXTEND_19(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_21(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,21)  EXTAND_ARGS(EXTEND_20(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_22(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,22)  EXTAND_ARGS(EXTEND_21(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_23(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,23)  EXTAND_ARGS(EXTEND_22(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_24(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,24)  EXTAND_ARGS(EXTEND_23(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_25(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,25)  EXTAND_ARGS(EXTEND_24(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_26(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,26)  EXTAND_ARGS(EXTEND_25(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_27(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,27)  EXTAND_ARGS(EXTEND_26(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_28(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,28)  EXTAND_ARGS(EXTEND_27(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_29(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,29)  EXTAND_ARGS(EXTEND_28(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_30(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,30)  EXTAND_ARGS(EXTEND_29(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_31(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,31)  EXTAND_ARGS(EXTEND_30(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_32(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,32)  EXTAND_ARGS(EXTEND_31(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_33(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,33)  EXTAND_ARGS(EXTEND_32(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_34(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,34)  EXTAND_ARGS(EXTEND_33(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_35(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,35)  EXTAND_ARGS(EXTEND_34(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_36(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,36)  EXTAND_ARGS(EXTEND_35(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_37(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,37)  EXTAND_ARGS(EXTEND_36(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_38(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,38)  EXTAND_ARGS(EXTEND_37(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_39(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,39)  EXTAND_ARGS(EXTEND_38(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_40(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,40)  EXTAND_ARGS(EXTEND_39(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_41(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,41)  EXTAND_ARGS(EXTEND_40(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_42(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,42)  EXTAND_ARGS(EXTEND_41(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_43(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,43)  EXTAND_ARGS(EXTEND_42(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_44(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,44)  EXTAND_ARGS(EXTEND_43(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_45(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,45)  EXTAND_ARGS(EXTEND_44(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_46(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,46)  EXTAND_ARGS(EXTEND_45(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_47(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,47)  EXTAND_ARGS(EXTEND_46(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_48(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,48)  EXTAND_ARGS(EXTEND_47(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_49(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,49)  EXTAND_ARGS(EXTEND_48(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_50(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,50)  EXTAND_ARGS(EXTEND_49(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_51(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,51)  EXTAND_ARGS(EXTEND_50(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_52(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,52)  EXTAND_ARGS(EXTEND_51(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_53(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,53)  EXTAND_ARGS(EXTEND_52(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_54(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,54)  EXTAND_ARGS(EXTEND_53(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_55(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,55)  EXTAND_ARGS(EXTEND_54(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_56(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,56)  EXTAND_ARGS(EXTEND_55(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_57(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,57)  EXTAND_ARGS(EXTEND_56(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_58(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,58)  EXTAND_ARGS(EXTEND_57(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_59(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,59)  EXTAND_ARGS(EXTEND_58(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_60(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,60)  EXTAND_ARGS(EXTEND_59(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_61(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,61)  EXTAND_ARGS(EXTEND_60(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_62(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,62)  EXTAND_ARGS(EXTEND_61(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_63(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,63)  EXTAND_ARGS(EXTEND_62(what,type,tagName,idName,idValue, __VA_ARGS__))
#define EXTEND_64(what,type,tagName,idName,idValue,propertyName, ...) what(type,tagName,idName,idValue,propertyName,64)  EXTAND_ARGS(EXTEND_63(what,type,tagName,idName,idValue, __VA_ARGS__))

#define CREATE_GET_ATTRIBUTE(type,tagName,idName,idValue,propertyName) \
QString get##idValue##_##propertyName(const QString &defValue=""){ \
    return getAttribute(createParameterStr(type,#tagName,#idName,#idValue),#propertyName,defValue);\
} \

#define CREATE_SET_ATTRIBUTE(type,tagName,idName,idValue,propertyName) \
bool set##idValue##_##propertyName(const QString &value,const int msg=-1,const void *data=nullptr){ \
    bool rt= setAttribute(createParameterStr(type,#tagName,#idName,#idValue),#propertyName,value);\
    if(msg>0) emit ValueChanged(msg,data);\
    return rt;\
} \

#define CREATE_EQUAL_ATTRIBUTE(idValue,propertyName) \
bool equal##idValue##_##propertyName(const QString &value,const QString &defValue=""){ \
    return get##idValue##_##propertyName(defValue.isEmpty() ? value:defValue).compare(value,Qt::CaseInsensitive)==0; \
} \

#define CREATE_GET_VALUE(type,tagName,idName,idValue) \
QString get##idValue##Value(const QString &defValue=""){ \
    return getValue(createParameterStr(type,#tagName,#idName,#idValue),defValue);\
} \

#define CREATE_SET_VALUE(type,tagName,idName,idValue) \
bool set##idValue##Value(const QString &value,const int msg=-1,const void *data=nullptr){ \
    bool rt=setNodeValue(createParameterStr(type,#tagName,#idName,#idValue),value);\
    if(msg>0) emit ValueChanged(msg,data);\
    return rt;\
} \

#define CREATE_EQUAL_VALUE(idValue) \
bool equal##idValue##Value(const QString &value,const QString &defValue=""){ \
    return get##idValue##Value(defValue.isEmpty() ? value:defValue).compare(value,Qt::CaseInsensitive)==0; \
} \

#define CREATE_GET_lIST(type,tagName,idName,idValue) \
bool get##_##idName##_##list(QVector<QString> &values){ \
    return getValues(createParameterStr(type,#tagName,#idName,#idValue),values);\
} \

#define CREATE_ATTRIBUTE(type,tagName,idName,idValue,propertyName) \
    CREATE_GET_ATTRIBUTE(type,tagName,idName,idValue,propertyName) \
    CREATE_SET_ATTRIBUTE(type,tagName,idName,idValue,propertyName) \
    CREATE_EQUAL_ATTRIBUTE(idValue,propertyName)

#define CREATE_VALUE(type,tagName,idName,idValue) \
    CREATE_GET_VALUE(type,tagName,idName,idValue) \
    CREATE_SET_VALUE(type,tagName,idName,idValue) \
    CREATE_EQUAL_VALUE(idValue)

#define CREATE_ATTRIBUTE_N(type,tagName,idName,idValue,propertyName,N) \
    CREATE_ATTRIBUTE(type,tagName,idName,idValue,propertyName)

#define ATTRIBUTE_FOR_EACH(type,tagName,idName,idValue,N,...) EXTAND_ARGS(CONCATENATE(EXTEND_, N)(CREATE_ATTRIBUTE_N,type,tagName,idName,idValue,__VA_ARGS__))

#define CREATE_ATTRIBUTES_EACH(type,tagName,idName,idValue,...) \
    CREATE_VALUE(type,tagName,idName,idValue) \
    ATTRIBUTE_FOR_EACH(type,tagName,idName,idValue,EXTAND_ARGS(FL_ARG_COUNT(__VA_ARGS__)),__VA_ARGS__)

#endif // DEF_PARAMETERS_H
