package cn.net.pikachu

import cn.net.pikachu.dao.InformationSchemaDAO
import cn.net.pikachu.model.Column
import cn.net.pikachu.model.Table
import cn.net.pikachu.model.View
import java.io.File

fun main(args: Array<String>) {
    val sb = StringBuilder()
    // 使用其他的数据库，修改这里
    val dbName = "yisong"
    val title = "${dbName}数据库设计文档"
    sb.append("# $title")
    val tableList = getTableList(dbName)
    generateTable(tableList, sb, dbName)
    val viewList = getViewList(dbName)
    if (viewList.isNotEmpty()) {
        sb.append("""
## 视图 (共${viewList.size}张)
""")
        for (view in viewList) {
            with(view) {
                sb.append("""
### $tableName
```sql
create or replace view $tableName as
$viewDefinition
;
```
                """)
            }
        }
    }
    val file = File("out.md")
    file.writeText(sb.toString())
    println("生成完毕")
}

private fun generateTable(tableList: List<Table>, sb: StringBuilder, dbName: String) {
    if (tableList.isNotEmpty()) {
        sb.append("""
## 表 (共${tableList.size}张)
""")
        for (table in tableList) {
            val tableName = table.tableName
            with(table) {
                sb.append("""
### $tableName (${table.tableComment})
| 字段| 类型| 特殊属性| 注释|
| -- | -- | ---- | -- |""")
            }
            val tableColumnList = getTableColumnList(dbName, tableName)
            for (col in tableColumnList) {
                with(col) {
                    sb.append("""
| $columnName| $columnType| ${getSpecialProperty()}| $columnComment|""")
                }
            }
            with(table) {
                sb.append("""
```sql
create table $tableName
(
${tableColumnList.joinToString(separator = ",\n") { it.toSql() }}
)
${if (tableComment.isNotEmpty()) "comment '$tableComment'" else ""}
${if (charset.isNotEmpty()) "charset $charset" else ""}
;
```
            """)
            }
        }
    }
}

fun getTableList(dbName: String): List<Table> {
    return InformationSchemaDAO.getTableList(dbName)
}

fun getTableColumnList(dbName: String, tableName: String): List<Column> {
    return InformationSchemaDAO.getTableColumnList(dbName, tableName)
}

fun getViewList(dbName: String): List<View> {
    return InformationSchemaDAO.getViewList(dbName)
}

fun Column.getSpecialProperty(): String {
    val extra = when (this.extra) {
        "auto_increment" -> "自增"
        "on update CURRENT_TIMESTAMP" -> "自动更新时间戳"
        else -> this.extra
    }
    val key = when (this.columnKey) {
        "PRI" -> "主键"
        "UNI" -> "唯一索引"
        else -> this.columnKey
    }
    if (extra.isNullOrEmpty()) {
        return key
    } else if (key.isNullOrEmpty()) {
        return extra
    } else {
        return "$extra, $key"
    }
}

val Column.defaultValue: String
    get() {
        return when (dataType) {
            "int" -> columnDefault ?: ""
            "timestamp" -> if (columnDefault == "CURRENT_TIMESTAMP") "CURRENT_TIMESTAMP" else "'$columnDefault'"
            "varchar" -> "'$columnDefault'"
            else -> ""
        }
    }

fun Column.toSql(): String {
    val sb = StringBuilder()
    sb.append("$columnName $columnType ")
    if (defaultValue.isNotEmpty()) {
        sb.append("default $defaultValue ")
    }
    when (isNullable) {
        "YES" -> sb.append("not null ")
        "NO" -> sb.append("null ")
    }
    if (extra.isNotEmpty()) {
        sb.append("$extra ")
    }
    if (columnComment.isNotEmpty()) {
        sb.append("comment '$columnComment'")
    }
    return sb.toString()
}

val Table.charset: String
    get () {
        if (tableCollation.isNullOrEmpty()) {
            return ""
        }
        if (tableCollation.startsWith("utf8mb4")) {
            return "utf8mb4"
        }
        if (tableCollation.startsWith("utf8")) {
            return "utf8"
        }
        return ""
    }
