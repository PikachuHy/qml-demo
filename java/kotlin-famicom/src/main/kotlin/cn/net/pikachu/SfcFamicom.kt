package cn.net.pikachu

abstract class SfcFamicom {
    fun init() {
        loadRom()
    }
    fun uninit() {
        freeRom()
    }
    protected abstract fun loadRom()
    protected abstract fun freeRom()
}