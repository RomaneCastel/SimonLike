#include "memoire.h"
#include <stdio.h>

void init_i2c_eeprom(LPC_I2C_TypeDef* I2Cx)
{
	uint32_t clockrate= 100000; // vitesse de fonctionnement du bus i2c, limit�e � 1 MHz
	I2C_Init(LPC_I2C0,clockrate); // initialisation du module i2c
	I2C_Cmd(LPC_I2C0, ENABLE);//on autorise les �changes i2C0 
}

 Status i2c_eeprom_write(uint16_t addr, uint8_t * data, int length) // �criture en m�moire d'un tableau de donn�es de taille length � partir de l'addresse addr
{
	int i;
	Status stat=ERROR;
	I2C_M_SETUP_Type cfgecriture; // cr�ation d'une structure pour la configuration pour une �criture de donn�es
  uint8_t newdata[MAX_NEWDATA_SIZE+1]; // cr�ation d'un tableau dont la premi�re case contient la fin de l'adresse de l'esclave
	newdata[0]=(addr&0xFF);
	for(i=1;i<=length;i++)
	{
		newdata[i]=data[i-1]; // on remplit le tableau avec les donn�es
	}
	cfgecriture.tx_data=newdata; // on initialise les param�tres du transfert : donn�es � �crire
	cfgecriture.tx_length=length+1; // longueur de la donn�e � transmettre
	cfgecriture.sl_addr7bit=((MEM_ADDR)>>1|(addr&0x700)>>8); //op�ration n�cessaire � toute transmission : slave ID + page 
	cfgecriture.rx_data=NULL; // on est pas en mode lecture
	cfgecriture.rx_length=0;
	stat=I2C_MasterTransferData(LPC_I2C0, &cfgecriture, I2C_TRANSFER_POLLING); // on appelle la fonction qui transf�re des donn�es sur le bus i2C en lui passant en param�tres la structure iniitlais�e pour l'�criture 
	return stat;
}

Status i2c_eeprom_read(uint16_t addr, uint8_t * read_data, int length) // lecture d'une donn�e en m�moire et r�cup�ration de cette donn�e dans un tableau
{
	Status stat=ERROR;
	I2C_M_SETUP_Type cfglecture; // cr�ation d'une structure  pour la configuration pour une lecture de donn�es
	uint16_t readaddress = addr & 0xFF; // adresse � laquelle on souhaite effectuer la lecture
	// configuration de l'�criture 
	cfglecture.tx_data=(uint8_t *)(&readaddress); //on �crit en m�moire l'adresse � laquelle on veut commencer � lire 
	cfglecture.tx_length=1; // on envoie l'adresse � laquelle on veut �crire qui fait 8 bits donc de longueur 1
	cfglecture.sl_addr7bit=((MEM_ADDR)>>1|(addr&0x700)>>8); //op�ration n�cessaire � toute transmission : slave ID ( pour reconnaitre  le periph�rique)+ page 
	// configuration de la lecture
	cfglecture.rx_data=read_data; // On stocke les donn�es lues dans le tableau read_data
	cfglecture.rx_length=length;
	stat=I2C_MasterTransferData(LPC_I2C0, &cfglecture, I2C_TRANSFER_POLLING);
	return stat;
}
