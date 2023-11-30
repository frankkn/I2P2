* 外部訪問
    * 像是直接在class外object_D.d
* 繼承訪問
    * 繼承D的class可以呼叫 out_protect()
* 同類訪問
    * 只有D可以呼叫out_private()

* protect/private的資料只能用在public寫函數的方式存取
    * 如果動用到protect資料，那只能由derived class呼叫
    * 如果動用到private資料，那只能由自己呼叫
* private成員無法被繼承(非private成員被繼承的方式由選擇的繼承方式決定)
    * public繼承: 保護程度不變
    * protected繼承: 都變為protected
    * private繼承: 都變為private