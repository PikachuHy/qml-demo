package cn.net.pikachu

data class SfcRomInfo(
//    val dataPrgrom: Int,
//    val dataChrrom: Int,
//    val countPrgrom16kb: Int,
//    val countChrrom8kb: Int,
    val mapperNumber: Int,
    val verticalMirroring: Boolean,
    val fourScreen: Boolean,
    val saveRam: Boolean,
    val reserved: List<Int>
)