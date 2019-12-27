//
// Created by pikachu on 2019/7/16.
//

#ifndef DATASTRUCTURES_DEBUG_H
#define DATASTRUCTURES_DEBUG_H

#include <stdio.h>
#define Debug printf("\nDebug:%s:%d:%s\t", __FILE__, __LINE__, __FUNCTION__);printf
#define Info printf("\nInfo:%s:%d:%s\t", __FILE__, __LINE__, __FUNCTION__);printf
#define Warning printf("\nWarning:%s:%d:%s\t", __FILE__, __LINE__, __FUNCTION__);printf
#define Fatal printf("\nFatal:%s:%d:%s\t", __FILE__, __LINE__, __FUNCTION__);printf
#endif //DATASTRUCTURES_DEBUG_H
