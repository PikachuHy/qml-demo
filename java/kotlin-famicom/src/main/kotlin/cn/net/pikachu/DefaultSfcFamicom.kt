package cn.net.pikachu

import cn.net.pikachu.enumeration.RomControlEnum

class DefaultSfcFamicom : SfcFamicom() {
    lateinit var header: SfcNesHeader
    lateinit var romInfo: SfcRomInfo
    override fun loadRom() {
        val filename = "nestest.nes"
        val stream = javaClass.classLoader.getResourceAsStream(filename)
        val bytes = stream.readBytes()
        var index = 0
        val magicNumber = String(bytes.copyOfRange(index, index + 4))
        index += 4
        val countPrgrom16kb = bytes[index++].toInt()
        val countChrrom8kb = bytes[index++].toInt()
        val control1 = bytes[index++].toInt()
        val control2 = bytes[index++].toInt()
        val reserved = bytes.copyOfRange(index, index + 4)
            .map { it.toInt() }

        header = SfcNesHeader(
            id = magicNumber,
            countPrgrom16kb = countPrgrom16kb,
            countChrrom8kb = countChrrom8kb
            )

        // 右移 >> shr
        // 或  ||  or
        // 与  &   and
        val mapperNumber = (control1 shr 4) or (control2 and 0xF0)
        val vmirroring = (control1 and RomControlEnum.SFC_NES_VMIRROR.value) > 0
        val fourScreen = (control1 and RomControlEnum.SFC_NES_4SCREEN.value) > 0
        val saveRam = (control1 and RomControlEnum.SFC_NES_SAVERAM.value) > 0

        romInfo = SfcRomInfo(
            mapperNumber = mapperNumber,
            verticalMirroring = vmirroring,
            fourScreen = fourScreen,
            saveRam = saveRam,
            reserved = listOf()
        )
    }

    override fun freeRom() {

    }
}