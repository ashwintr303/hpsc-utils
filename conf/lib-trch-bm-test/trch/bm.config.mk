TEST_FLOAT 				= 1
TEST_SYSTICK			= 1
TEST_WDTS 				= 1
TEST_TRCH_DMA			= 1
TEST_TRCH_DMA_CB 		= 1 # if set, use callback, otherwise call dma_wait

# TODO: The test passes, but subsequent boot of RTPS fails (Uboot loads, but
# upon transfer to baremetal, qemu crashes with:
# qemu: fatal: Lockup: can't escalate 3 to HardFault (current priority -1)
TEST_RT_MMU				= 0

TEST_ETIMER				= 1
TEST_RTI_TIMER			= 1
TEST_SHMEM				= 1
