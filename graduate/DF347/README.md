# DF347

[云计算时代的大数据查询分析优化](https://www.datafountain.cn/competitions/347)源码

## 测试baseline

### 文件读取

- customer


|时间|1.5M|15M|
|--|--|--|
|2019年10月13日|0.2|无|
|2019年10月17日|0.055|0.56|


- lineitem


|时间|1M|1M|100M| 10亿| 全量|
|--|--|--|--|--| --|
|2019年10月13日|0.3|3.1|31|无|无|
|-|0.1|1.1|11|无|无|
|-|0.09|0.7|8.2|无|无|
|2019年10月14日|0.12|0.98|10.4|无|无|
|2019年10月17日|0.055|0.48|6.37|无|无|
|2019年10月18日|0.050|0.52|6.38|崩溃|无|


- orders


|时间|1.5M|15M|150M|
|--|--|--|--|
|2019年10月13日|0.4|4.0|41|
|-|0.15|1.23|12.8|
|2019年10月17日|0.093|0.93|10.6|

```c
0.4 4.0 41
fscanf(fp, "%d|%d|%s", &orders[i].orderkey, &orders[i].custkey, date);
```

```c
0.8 9 无
fread(buffer, 1, 20, fp);
convert2order(buffer, &orders[i]);

static void convert2order(const char * buffer, Order *order) {
    int index = 0;
    int key = 0;
    while(buffer[index] != '|') {
        key = key * 10 + buffer[index] - '0';
        index++;
    }
    order->orderkey = key;
    key = 0;
    index++;
    while(buffer[index] != '|') {
        key = key * 10 + buffer[index] - '0';
        index++;
    }
    order->custkey = key;
    int date = 0;
    index++;
    while (buffer[index] != '\0') {
        if (buffer[index] == '-') {
            index++;
            continue;
        }
        date = date * 10 + buffer[index] - '0';
        index++;
    }
    order->orderdate = date;
}

```
```c
0.17 1.6 17
fgets(buffer, 30, fp);
convert2order(buffer, &orders[i]);
```
```c
 0.13 1.1 13
Order* ReadOrderTable(const char* path, int rowCount) {
    Order* order = malloc(sizeof(Order) * rowCount);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    for (int i = 0; i < rowCount; ++i) {
        int key = 0;
        while(*buffer != '|') {
            key = key * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        order[i].orderkey = key;
        key = 0;
        while (*buffer != '|') {
            if(*buffer == '.') {
                buffer++;
                continue;
            }
            key = key * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        order[i].custkey = key;
        int date = 0;
        while (*buffer!='\n') {
            if (*buffer == '-') {
                buffer++;
                continue;
            }
            date = date * 10 + *buffer - '0';
            buffer++;
        }
        order[i].orderdate = date;
    }
    munmap(start, sb.st_size);
    close(fd);
    return order;
}
```

### 表连接

- 测试参数 1 19950329 19950327 5

|时间|customer|orders|lineitem|cost|
|--|--|--|--|--|--|
|2019年10月14日|150，000|10，000|10，000|0.49|
|-|150，000|10，000|10，000，000|0.62|
|-|150，000|1,000，000|1，000，000|50|

### 建立索引

- 测试参数 1 19950329 19950327 5

| 时间           | customer | orders | lineitem | customer index cost | order index cost | lineitem index cost |
| -------------- | -------- | ------ | -------- | ------------------- | ---------------- | ------------------- |
| 2019年10月14日 | 15M      | 10M    | 10M      | 0.10                | 17.3             | 4.5                 |

- 仅Order

| 时间           | orders | index cost |
| -------------- | ------ | ---------- |
| 2019年10月16日 | 1M     | 2.3        |
|                | 10M    | 14.0       |
| 2019年10月17日 | 1M     | 0.16       |
|                | 10M    | 0.52       |
|                | 100M   | 5.84       |
| 2019年10月18日 | 1M     | 0.33       |
|                | 10M    | 1.91       |
|                | 100M   | 18.7       |
|                | 150M   | 27.3       |

- 仅Lineitem

| 时间           | orders | index cost |
| -------------- | ------ | ---------- |
| 2019年10月16日 | 1M     | 0.35       |
|                | 10M    | 3.95       |
| 2019年10月17日 | 1M     | 0.047      |
|                | 10M    | 0.45       |
|                | 100M   | 内存不足   |
| 2019年10月18日 | 1M     | 0.042      |
|                | 10m    | 0.42       |
|                | 100M   | 7.14       |




### 建立索引再连接

- 测试参数 1 19950329 19950327 5

| 时间           | customer | orders     | lineitem    | index cost | Join cost | total cost |
| -------------- | -------- | ---------- | ----------- | ---------- | --------- | ---------- |
| 2019年10月14日 | 150，000 | 1,000，000 | 1，000，000 | 0.000853   | 52        | 52         |
|                | 150，000 | 100，000   | 100，000    | 0.000876   | 5.06      | 5          |
|                | 15M      | 0.1M       | 0.1M        | 1.16       | 1.62      | 2.8        |
|                | 15M      | 0.1M       | 0.1M        | 1.19       | 0.03      | 1.22       |
|                | 15M      | 1M         | 1M          | 2.95       | 0.18      | 3.13       |
|                | 15M      | 10M        | 1M          | 19         | 3.3       | 22.3       |
|                | 15M      | 10M        | 10M         | 23         | 3.4       | 26.4       |
| 2019年10月18日 | 15M      | 30M        | 30M         | 7.96       | 14.35     | 22.31      |

### 完整流程

- 测试参数 1 19950329 19950327 5

| 时间           | orders | lineitem | cost |
| -------------- | ------ | -------- | ---- |
| 2019年10月18日 | 10M    | 10M      | 7.80 |
|                | 20M    | 10M      | 11.9 |
|                | 20M    | 20M      | 13.0 |
|                | 30M    | 20M      | 26.2 |
|                | 30M    | 30M      | 25.6 |

## 服务器版本

### 文件读取


- customer


|时间|1.5M|15M|
|--|--|--|
|2019年10月21日| 0.203 | 0.25 |
|                |       |      |


- lineitem


|时间|1M|1M|100M| 10亿| 全量|
|--|--|--|--|--| --|
|2019年10月21日|0.3|3.1|31|无|无|


- orders


|时间|1.5M|15M|150M|
|--|--|--|--|
|2019年10月21日|0.0258|0.290|3.183|

### 建立索引

- 仅Customer

| 时间           | customer | index cost |
| -------------- | ------ | ---------- |
| 2019年10月21日 | 15M     | 0.0450        |


- 仅Order

| 时间           | orders | index cost |
| -------------- | ------ | ---------- |
| 2019年10月21日 | 10M     | 0.251        |
| 2019年10月21日 | 100M     | 2.32        |
| 2019年10月21日 | 150M     | 21.6       |


- 仅Lineitem

| 时间           | lineitem | index cost |
| -------------- | ------ | ---------- |
| 2019年10月21日 | 1M     | 0.0124       |
| 2019年10月21日 | 10M     | 0.190       |
| 2019年10月21日 | 100M     | 1.98       |
| 2019年10月21日 | 全量     | 12.4       |

### 完整流程
- 测试参数 1 19950329 19950327 5

| 时间           | Data          | read  | index | join  | group & sum | topn  | Total |
| -------------- | ------------- | ----- | ----- | ----- | ----------- | ----- | ----- |
| 2019年10月18日 | 15M+3M+3M     | 0.311 | 0.777 | 0.202 | 0.311       | 0.151 | 17.8  |
|                | 15M+30M+30M   | 1.21  | 6.68  | 0.921 | 0.319       | 0.150 | 25.8  |
|                | 15M+100M+100M | 3.64  | 22.1  | 3.48  | 0.330       | 0.153 | 46.3  |
|                | 15M+150M+300M | 6.52  | 32.5  | 6.5   | 0.379       | 0.159 | 61.2  |
|                | 15M+150M+500M | 9.13  | 58.19 | 17.1  | 0.810       | 0.860 | 101   |
|                | 15M+150M+600M | 10.4  | 55.8  | 17.0  | 0.908       | 0.511 | 110   |
|                | 全量          | 12.6  | 36.8  | 37.9  | 0.915       | 0.866 | 117   |

注意：全量数据内存占用 128G * 56%

#### 读取数据时，剪枝

- 测试参数 1 19950329 19950327 5


| 时间           | Data | read  | index | join | query | Total |
| -------------- | ---- | ----- | ----- | ---- | ----- | ----- |
| 2019年10月27日 | 全量 | 10.57 | 34.06 | 4.93 | 1.055 | 52.68 |

- 测试参数 3 BUILDING 1995-03-29 1995-03-27 5 BUILDING 1995-02-29 1995-04-27 10 BUILDING 1995-03-28 1995-04-27 2


| 时间           | Data | read  | index | join | query | Total |
| -------------- | ---- | ----- | ----- | ---- | ----- | ----- |
| 2019年10月27日 | 全量 | 10.57 | 33.89 | 4.93 | 1.055 | 61.76 |

#### 写死日期范围


- 测试参数 1 19950329 19950327 5

只跑出一次这个结果


| 时间           | Data | read  | index | join | query | Total |
| -------------- | ---- | ----- | ----- | ---- | ----- | ----- |
| 2019年10月27日 | 全量 | 12.21 | 20.11 | 4.68 | 1.189 | 40.47 |

- 测试参数 3 BUILDING 1995-03-29 1995-03-27 5 BUILDING 1995-02-29 1995-04-27 10 BUILDING 1995-03-28 1995-04-27 2

无提升