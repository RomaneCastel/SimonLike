#include "memoire.h"
#include <stdio.h>

void init_i2c_eeprom(LPC_I2C_TypeDef* I2Cx)
{
	uint32_t clockrate= 100000; // vitesse de fonctionnement du bus i2c, limitée à 1 MHz
	I2C_Init(LPC_I2C0,clockrate); // initialisation du module i2c
	I2C_Cmd(LPC_I2C0, ENABLE);//on autorise les échanges i2C0 
}

 Status i2c_eeprom_write(uint16_t addr, uint8_t * data, int length) // écriture en mémoire d'un tableau de données de taille length à partir de l'addresse addr
{
	int i;
	Status stat=ERROR;
	I2C_M_SETUP_Type cfgecriture; // création d'une structure pour la configuration pour une écriture de données
  uint8_t newdata[MAX_NEWDATA_SIZE+1]; // création d'un tableau dont la première case contient la fin de l'adresse de l'esclave
	newdata[0]=(addr&0xFF);
	for(i=1;i<=length;i++)
	{
		newdata[i]=data[i-1]; // on remplit le tableau avec les données
	}
	cfgecriture.tx_data=newdata; // on initialise les paramètres du transfert : données à écrire
	cfgecriture.tx_length=length+1; // longueur de la donnée à transmettre
	cfgecriture.sl_addr7bit=((MEM_ADDR)>>1|(addr&0x700)>>8); //opération nécessaire à toute transmission : slave ID + page 
	cfgecriture.rx_data=NULL; // on est pas en mode lecture
	cfgecriture.rx_length=0;
	stat=I2C_MasterTransferData(LPC_I2C0, &cfgecriture, I2C_TRANSFER_POLLING); // on appelle la fonction qui transfère des données sur le bus i2C en lui passant en paramètres la structure iniitlaisée pour l'écriture 
	return stat;
}

Status i2c_eeprom_read(uint16_t addr, uint8_t * read_data, int length) // lecture d'une donnée en mémoire et récupération de cette donnée dans un tableau
{
	Status stat=ERROR;
	I2C_M_SETUP_Type cfglecture; // création d'une structure  pour la configuration pour une lecture de données
	uint16_t readaddress = addr & 0xFF; // adresse à laquelle on souhaite effectuer la lecture
	// configuration de l'écriture 
	cfglecture.tx_data=(uint8_t *)(&readaddress); //on écrit en mémoire l'adresse à laquelle on veut commencer à lire 
	cfglecture.tx_length=1; // on envoie l'adresse à laquelle on veut écrire qui fait 8 bits donc de longueur 1
	cfglecture.sl_addr7bit=((MEM_ADDR)>>1|(addr&0x700)>>8); //opération nécessaire à toute transmission : slave ID ( pour reconnaitre  le periphérique)+ page 
	// configuration de la lecture
	cfglecture.rx_data=read_data; // On stocke les données lues dans le tableau read_data
	cfglecture.rx_length=length;
	stat=I2C_MasterTransferData(LPC_I2C0, &cfglecture, I2C_TRANSFER_POLLING);
	return stat;
}
