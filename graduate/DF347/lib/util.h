//
// Created by PikachuHy on 2019/10/13.
//

#ifndef DF347_UTIL_H
#define DF347_UTIL_H
#define sdate2idate(idate, sdate) \
idate = \
 (sdate[0] - '0') * 10000000 \
+(sdate[1] - '0') * 1000000 \
+(sdate[2] - '0') * 100000 \
+(sdate[3] - '0') * 10000 \
+(sdate[5] - '0') * 1000 \
+(sdate[6] - '0') * 100 \
+(sdate[8] - '0') * 10 \
+(sdate[9] - '0') ;
#endif //DF347_UTIL_H
