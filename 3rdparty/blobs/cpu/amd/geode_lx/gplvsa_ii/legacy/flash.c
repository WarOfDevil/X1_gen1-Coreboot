/*
* Copyright (c) 2006-2008 Advanced Micro Devices,Inc. ("AMD").
*
* This library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2.1 of the
* License, or (at your option) any later version.
*
* This code is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General
* Public License along with this library; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place, Suite 330,
* Boston, MA 02111-1307 USA 
*/

//******************************************************************************
//*    Routines related to the Flash device.  
//******************************************************************************





#include "VSA2.H"
#include "CHIPSET.H"
#include "SYSMGR.H"
#include "MDD.H"
#include "PCI.H"
#include "GX2.H"
#include "LEGACY.H"
#include "PROTOS.H"

// Function prototypes:
extern void Hide_IDE_Hdr(void);
extern void Hide_Flash_Hdr(void);


// External variables:
extern ULONG MDD_Base;
extern USHORT Flash_Function, IDE_Function;
extern UCHAR Flash_Allocated;



//***********************************************************************
// Returns non-zero if Flash device is enabled
//***********************************************************************
UCHAR FlashIsEnabled(void)
{ UCHAR Pin;

  Pin = (UCHAR)Read_MSR_LO(MDD_Base + MSR_PIN_OPTS) & PIN_OPT_IDE;
  Pin ^= PIN_OPT_IDE;
  return Pin;
}


//***********************************************************************
// Allocates Flash BARs
//***********************************************************************
void Allocate_Flash_BARs(void)
{ ULONG MsrAddr, MsrData[2], Size;
  USHORT Bar;
  UCHAR Resource;
  static UCHAR Flash_LBARs[4] = {
    MSR_LBAR_FLSH0,
    MSR_LBAR_FLSH1,
    MSR_LBAR_FLSH2,
    MSR_LBAR_FLSH3,
  };


  // BARs are only to be allocated once
  if (Flash_Allocated == 0) {

    Flash_Allocated = 1;
    // Determine type/size of PCI BAR for each Flash device
    MsrAddr = MDD_Base;
    for (Bar = BAR0; Bar <= BAR3; Bar += 4) {
      // Read the Flash LBAR
      (UCHAR)MsrAddr = Flash_LBARs[(Bar-BAR0)/4];
      Read_MSR(MsrAddr, MsrData);

      // If LBAR size has not been programmed, then don't configure the PCI BAR
      Size = MsrData[1] & ~(MEM_IO | NOR_NAND | LBAR_EN);
      if (Size == 0x00000000) {
        continue;
      }

      // MMIO or IO resource
      if (MsrData[1] & MEM_IO ) {
        // MMIO mode
        Size &= LBAR_MEM_MASK;
        Resource = RESOURCE_MMIO;
      } else {
        // IO mode
        // Required for proper byte count calculation
        Size |= 0xFFFF0000;
        Resource = RESOURCE_IO;
      }
      // Convert mask to byte count
      Size = ~Size + 1;
      // Allocate BAR
      SYS_ALLOCATE_RESOURCE(Resource, Bar, Size, DEVICE_ID_AMD_FLASH, ID_MDD);
    }
  }
}



//***********************************************************************
// Switches between Flash and IDE headers
//***********************************************************************
void pascal Flash_IDE_Switch(USHORT Function, ULONG Data)
{ ULONG PinOptions, PinMsr, FlashMsr, LBar[2], SavedLBar[2];

  // Switch pins to Flash mode
  PinMsr = MDD_Base + MSR_PIN_OPTS;
  PinOptions = Read_MSR_LO(PinMsr);

  if (Function == Flash_Function) {
    // Currently in Flash mode

    // Switching to IDE mode ?
    if (Data == 0xBEEFDEAD) {

      // Hide the Flash header
      Hide_Flash_Hdr();

      // Switch pins to IDE mode
      PinOptions |= PIN_OPT_IDE;
      Write_MSR_LO(PinMsr, PinOptions);

      // Disconnect the ROM from the DMA pins
      in_8(0x3F6);
    }

  }	else {

    // Currently in IDE mode

    // Switching to Flash mode ?
    if (Data == 0xDEADBEEF) {

      // Hide the IDE header
      Hide_IDE_Hdr();

      // Allocate Flash BARs
      Allocate_Flash_BARs();

      // Enable Flash mode
      PinOptions &= ~PIN_OPT_IDE;
      Write_MSR_LO(PinMsr, PinOptions);

      // Handle Canary circuit

      // Set CS1# to respond to I/O address 22h
      FlashMsr = MDD_Base + MSR_LBAR_FLSH1;
      Read_MSR(FlashMsr, SavedLBar);
      LBar[0] = 0x00000022;
      LBar[1] = 0x0000FFF0 | LBAR_EN;
      Write_MSR(FlashMsr, LBar);

      // Turn Canary circuit on
      in_8(0x22);

      // Restore CS1 LBAR
      Write_MSR(FlashMsr, SavedLBar);
    }
  }
}
