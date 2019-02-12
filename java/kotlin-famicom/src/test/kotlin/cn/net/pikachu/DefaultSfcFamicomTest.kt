package cn.net.pikachu

import cn.net.pikachu.annotation.AllOpen
import org.junit.After
import org.junit.Before
import org.junit.Test

import org.junit.Assert.*
@AllOpen
class DefaultSfcFamicomTest {
    lateinit var sfcFamicom: DefaultSfcFamicom
    @Before
    fun setUp() {
        sfcFamicom = DefaultSfcFamicom()
        sfcFamicom.init()
    }

    @After
    fun tearDown() {
        sfcFamicom.uninit()
    }

    @Test
    fun loadRom() {
        val (
                id,
                countPrgrom16kb,
                countChrrom8kb
        ) = sfcFamicom.header
        assertEquals("NES\u001A", id)
        assertEquals(1, countPrgrom16kb)
        assertEquals(1, countChrrom8kb)
        val (
                mapperNumber,
                verticalMirroring,
                fourScreen,
                saveRam,
                _
        ) = sfcFamicom.romInfo
        assertEquals(0, mapperNumber)
        assertFalse(verticalMirroring)
        assertFalse(fourScreen)
        assertFalse(saveRam )
    }
}