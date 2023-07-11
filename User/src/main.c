/*
 * @Author       : ZakiuC
 * @Date         : 2023-07-05 10:17:32
 * @LastEditors  : ZakiuC z2337070680@163.com
 * @LastEditTime : 2023-07-07 16:54:47
 * @FilePath     : \User\src\main.c
 * @Description  : 
 * Copyright (c) 2023 by ZakiuC z2337070680@163.com, All Rights Reserved. 
 */
#include "main.h"
#include <stdbool.h>
#include "aes.h"


#define ApplicationAddress    ((uint32_t)0x08002000)   //APP Program start address
#define IaplicationAddress    ((uint32_t)0x08000000)   //IAP Program start address

// ��ŵ�ַ
#define DATA_ADDRESS 0x801FC00
#define DATA_ADDRESS_END 0x801FFFF

#define CHIPUID_ADDRESS 0x1FFFF7AC
// ҳ��С
#define FLASH_PAGE_SIZE ((uint32_t)0x00000200) 
// uid����
#define UIDLENGTH 12

typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;

#define DEBUGMODE 0

#if DEBUGMODE
uint8_t data1[16];
uint8_t data2[16];
uint8_t data3[16];
#endif

_Bool check_data() {
	// 加密数据
    uint8_t encrypted_data[16];
    // 解密数据
	uint8_t decrypted_data[16];
    // uid
	uint8_t chip_uid[16];
	// 密钥
    uint8_t key[16] = {0xAC, 0xF5, 0x8E, 0xDD, 0xC1, 0xC4, 0x81, 0x6A, 0xC9, 0xCC, 0x52, 0x1C, 0x00, 0x00, 0x00, 0x00}; // 加密密钥
	uint32_t erase_counter = 0x00;
	
	// 初始化AES_ctx结构体
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

	
   // 读数据
   if ((*(uint32_t*)(DATA_ADDRESS) != (uint32_t)0 && *(uint32_t*)(DATA_ADDRESS + 4) != (uint32_t)0 && *(uint32_t*)(DATA_ADDRESS + 8) != (uint32_t)0 ) || (
	   (*(uint32_t*)(DATA_ADDRESS) != (uint32_t)0xFFFFFFFF && *(uint32_t*)(DATA_ADDRESS + 4) != (uint32_t)0xFFFFFFFF && *(uint32_t*)(DATA_ADDRESS + 8) != (uint32_t)0xFFFFFFFF )))
	{
		// 获取芯片的UID和密文
		for(uint8_t i = 0 ;i < 16;i++)
		{
			encrypted_data[i] = *(uint8_t*)(DATA_ADDRESS + i);
			chip_uid[i] = *(uint8_t*)(CHIPUID_ADDRESS + i);
#if DEBUGMODE
			data1[i] = chip_uid[i];
			data2[i] = encrypted_data[i];
#endif
		}
		
		memcpy(decrypted_data, encrypted_data, sizeof(encrypted_data));
		AES_ECB_decrypt(&ctx, decrypted_data);
#if DEBUGMODE
		for(uint8_t j = 0;j < 16; j++)
		{
			data3[j] = decrypted_data[j];
		}
#endif
		// 比较解密后的数据与芯片UID是否匹配
		if (memcmp(decrypted_data, chip_uid, UIDLENGTH) == 0) {
			// 如果匹配，则正常执行程序
			return true;
		} else {
			// 如果不匹配，则执行其他操作
			return false;
		}
	} else {
		// 如果读取失败，则执行加密过程
		// 获取芯片的UID
		for(uint8_t i = 0 ;i < UIDLENGTH;i++)
		{
			chip_uid[i] = *(uint8_t*)(CHIPUID_ADDRESS + i);
#if DEBUGMODE
			data1[i]= chip_uid[i];
#endif
		}
		// 补满16位
		memset(chip_uid + UIDLENGTH, '\0', sizeof(chip_uid) - UIDLENGTH);
		// 加密芯片UID
		memcpy(encrypted_data, chip_uid, sizeof(chip_uid));
		AES_ECB_encrypt(&ctx, encrypted_data);
#if DEBUGMODE		
		for(uint8_t j=0;j< 16;j++)
		{
			data2[j]= encrypted_data[j];
		}
#endif
		// 解锁flash
		FLASH_Unlock();

		uint32_t number_of_page = (DATA_ADDRESS_END - DATA_ADDRESS) / FLASH_PAGE_SIZE;

		for (erase_counter = 0; (erase_counter < number_of_page); erase_counter++)
		{
			if (FLASH_ErasePage(DATA_ADDRESS + (FLASH_PAGE_SIZE * erase_counter)) != FLASH_COMPLETE)
			{
				// 错误处理
				while (1)
				{
				}
			}
		}
		
		uint32_t address = DATA_ADDRESS;

		while (address < DATA_ADDRESS_END)
		{
			uint32_t data = *((uint32_t*)&encrypted_data[address - DATA_ADDRESS]);
			if (FLASH_ProgramWord(address, data) == FLASH_COMPLETE)
			{
				address = address + 4;
			}
			else
			{
				// 错误处理
				while (1)
				{
				}
			}
		}
		// 锁回去
		FLASH_Lock();
		// 重启
		NVIC_SystemReset();
   }   
}

int main(void)
{
#if DEBUGMODE
	check_data();
#else
	if(check_data())
	{
		// 跳转至app
		if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
        { 
            /* Jump to user application */
            JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
            Jump_To_Application = (pFunction) JumpAddress;
            /* Initialize user application's Stack Pointer */
            __set_MSP(*(__IO uint32_t*) ApplicationAddress);
            __disable_irq();
			Jump_To_Application();
        }
	}else{
		// 擦除所有扇区数据
//		FLASH_EraseAllPages();
		// 软重启
		NVIC_SystemReset();
	}
#endif
}


