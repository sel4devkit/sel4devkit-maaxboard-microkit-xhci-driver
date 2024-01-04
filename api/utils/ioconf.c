#include "ioconf.h"
/*
 * MACHINE GENERATED: DO NOT EDIT
 *
 * ioconf.c, from "/home/adunne/netbsd/src/sys/arch/evbarm/conf/netbsd"
 */

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/device.h>
#ifndef SEL4
#include <sys/mount.h>
#endif

static const struct cfiattrdata wskbddevcf_iattrdata = {
	"wskbddev", 2, {
		{ "console", "-1", -1 },
		{ "mux", "1", 1 },
	}
};
static const struct cfiattrdata sunxide2buscf_iattrdata = {
	"sunxide2bus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata rkfbbuscf_iattrdata = {
	"rkfbbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata wsmousedevcf_iattrdata = {
	"wsmousedev", 1, {
		{ "mux", "0", 0 },
	}
};
static const struct cfiattrdata midibuscf_iattrdata = {
	"midibus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata tegra210xpadcf_iattrdata = {
	"tegra210xpad", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata vchiqbuscf_iattrdata = {
	"vchiqbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata radeonfbbuscf_iattrdata = {
	"radeonfbbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata nvmecf_iattrdata = {
	"nvme", 1, {
		{ "nsid", "-1", -1 },
	}
};
static const struct cfiattrdata drmcf_iattrdata = {
	"drm", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata acpibuscf_iattrdata = {
	"acpibus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata puccf_iattrdata = {
	"puc", 1, {
		{ "port", "-1", -1 },
	}
};
static const struct cfiattrdata irbuscf_iattrdata = {
	"irbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata usbuscf_iattrdata = {
	"usbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata acpihpetbuscf_iattrdata = {
	"acpihpetbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata rkiomuxcf_iattrdata = {
	"rkiomux", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata miicf_iattrdata = {
	"mii", 1, {
		{ "phy", "-1", -1 },
	}
};
static const struct cfiattrdata acpiwdrtbuscf_iattrdata = {
	"acpiwdrtbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata spicf_iattrdata = {
	"spi", 1, {
		{ "slave", "-1", -1 },
	}
};
static const struct cfiattrdata acpinodebuscf_iattrdata = {
	"acpinodebus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata acpimadtbuscf_iattrdata = {
	"acpimadtbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata i2cbuscf_iattrdata = {
	"i2cbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata atapicf_iattrdata = {
	"atapi", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata scsicf_iattrdata = {
	"scsi", 1, {
		{ "channel", "-1", -1 },
	}
};
static const struct cfiattrdata spiflashbuscf_iattrdata = {
	"spiflashbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata rkpmiccf_iattrdata = {
	"rkpmic", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata mskccf_iattrdata = {
	"mskc", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata usbififcf_iattrdata = {
	"usbifif", 6, {
		{ "port", "-1", -1 },
		{ "configuration", "-1", -1 },
		{ "interface", "-1", -1 },
		{ "vendor", "-1", -1 },
		{ "product", "-1", -1 },
		{ "release", "-1", -1 },
	}
};
static const struct cfiattrdata hdaudiobuscf_iattrdata = {
	"hdaudiobus", 1, {
		{ "nid", "-1", -1 },
	}
};
static const struct cfiattrdata sunxifbbuscf_iattrdata = {
	"sunxifbbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata gpiobuscf_iattrdata = {
	"gpiobus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata scsibuscf_iattrdata = {
	"scsibus", 2, {
		{ "target", "-1", -1 },
		{ "lun", "-1", -1 },
	}
};
static const struct cfiattrdata atacf_iattrdata = {
	"ata", 1, {
		{ "channel", "-1", -1 },
	}
};
static const struct cfiattrdata usbdevifcf_iattrdata = {
	"usbdevif", 6, {
		{ "port", "-1", -1 },
		{ "configuration", "-1", -1 },
		{ "interface", "-1", -1 },
		{ "vendor", "-1", -1 },
		{ "product", "-1", -1 },
		{ "release", "-1", -1 },
	}
};
static const struct cfiattrdata audiocf_iattrdata = {
	"audio", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata gpiocf_iattrdata = {
	"gpio", 3, {
		{ "offset", "-1", -1 },
		{ "mask", "0", 0 },
		{ "flag", "0", 0 },
	}
};
static const struct cfiattrdata axppmiccf_iattrdata = {
	"axppmic", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata uhidbuscf_iattrdata = {
	"uhidbus", 1, {
		{ "reportid", "-1", -1 },
	}
};
static const struct cfiattrdata spibuscf_iattrdata = {
	"spibus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata rkusbcf_iattrdata = {
	"rkusb", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata radiodevcf_iattrdata = {
	"radiodev", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata ucombuscf_iattrdata = {
	"ucombus", 1, {
		{ "portno", "-1", -1 },
	}
};
static const struct cfiattrdata acpiecdtbuscf_iattrdata = {
	"acpiecdtbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata sdmmccf_iattrdata = {
	"sdmmc", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata plcomcf_iattrdata = {
	"plcom", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata applesmcbuscf_iattrdata = {
	"applesmcbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata cpucf_iattrdata = {
	"cpu", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata pcicf_iattrdata = {
	"pci", 2, {
		{ "dev", "-1", -1 },
		{ "function", "-1", -1 },
	}
};
static const struct cfiattrdata wsbelldevcf_iattrdata = {
	"wsbelldev", 2, {
		{ "console", "-1", -1 },
		{ "mux", "1", 1 },
	}
};
static const struct cfiattrdata pcibuscf_iattrdata = {
	"pcibus", 1, {
		{ "bus", "-1", -1 },
	}
};
static const struct cfiattrdata as3722pmiccf_iattrdata = {
	"as3722pmic", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata virtiocf_iattrdata = {
	"virtio", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata dtvbuscf_iattrdata = {
	"dtvbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata atapibuscf_iattrdata = {
	"atapibus", 1, {
		{ "drive", "-1", -1 },
	}
};
static const struct cfiattrdata sdmmcbuscf_iattrdata = {
	"sdmmcbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata bcmmboxbuscf_iattrdata = {
	"bcmmboxbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata btbuscf_iattrdata = {
	"btbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata bthubcf_iattrdata = {
	"bthub", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata wsemuldisplaydevcf_iattrdata = {
	"wsemuldisplaydev", 2, {
		{ "console", "-1", -1 },
		{ "kbdmux", "1", 1 },
	}
};
static const struct cfiattrdata acpiapmbuscf_iattrdata = {
	"acpiapmbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata mpcorebuscf_iattrdata = {
	"mpcorebus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata hdmicecbuscf_iattrdata = {
	"hdmicecbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata acpigtdtbuscf_iattrdata = {
	"acpigtdtbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata fdtcf_iattrdata = {
	"fdt", 1, {
		{ "pass", "10", 10 },
	}
};
static const struct cfiattrdata iiccf_iattrdata = {
	"iic", 1, {
		{ "addr", "-1", -1 },
	}
};
static const struct cfiattrdata audiobuscf_iattrdata = {
	"audiobus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata videobuscf_iattrdata = {
	"videobus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata ata_hlcf_iattrdata = {
	"ata_hl", 1, {
		{ "drive", "-1", -1 },
	}
};
static const struct cfiattrdata comcf_iattrdata = {
	"com", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata acpisdtbuscf_iattrdata = {
	"acpisdtbus", 0, {
		{ NULL, NULL, 0 },
	}
};
static const struct cfiattrdata usbroothubifcf_iattrdata = {
	"usbroothubif", 0, {
		{ NULL, NULL, 0 },
	}
};

CFDRIVER_DECL(swwdog, DV_DULL, NULL);

static const struct cfiattrdata * const spkr_attrs[] = { &wsbelldevcf_iattrdata, NULL };
CFDRIVER_DECL(spkr, DV_DULL, spkr_attrs);

static const struct cfiattrdata * const audio_attrs[] = { &audiocf_iattrdata, NULL };
CFDRIVER_DECL(audio, DV_AUDIODEV, audio_attrs);

static const struct cfiattrdata * const midi_attrs[] = { &audiocf_iattrdata, NULL };
CFDRIVER_DECL(midi, DV_DULL, midi_attrs);

static const struct cfiattrdata * const hdaudio_attrs[] = { &hdaudiobuscf_iattrdata, NULL };
CFDRIVER_DECL(hdaudio, DV_DULL, hdaudio_attrs);

static const struct cfiattrdata * const hdafg_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(hdafg, DV_DULL, hdafg_attrs);

CFDRIVER_DECL(video, DV_DULL, NULL);

CFDRIVER_DECL(dtv, DV_DULL, NULL);

CFDRIVER_DECL(hdmicec, DV_DULL, NULL);

CFDRIVER_DECL(spdmem, DV_DULL, NULL);

static const struct cfiattrdata * const iic_attrs[] = { &iiccf_iattrdata, NULL };
CFDRIVER_DECL(iic, DV_DULL, iic_attrs);

CFDRIVER_DECL(pcf8563rtc, DV_DULL, NULL);

CFDRIVER_DECL(seeprom, DV_DULL, NULL);

CFDRIVER_DECL(dsrtc, DV_DULL, NULL);

static const struct cfiattrdata * const axppmic_attrs[] = { &axppmiccf_iattrdata, NULL };
CFDRIVER_DECL(axppmic, DV_DULL, axppmic_attrs);

static const struct cfiattrdata * const axpreg_attrs[] = { &axppmiccf_iattrdata, NULL };
CFDRIVER_DECL(axpreg, DV_DULL, axpreg_attrs);

CFDRIVER_DECL(titemp, DV_DULL, NULL);

static const struct cfiattrdata * const as3722pmic_attrs[] = { &as3722pmiccf_iattrdata, NULL };
CFDRIVER_DECL(as3722pmic, DV_DULL, as3722pmic_attrs);

static const struct cfiattrdata * const as3722reg_attrs[] = { &as3722pmiccf_iattrdata, NULL };
CFDRIVER_DECL(as3722reg, DV_DULL, as3722reg_attrs);

CFDRIVER_DECL(max77620pmic, DV_DULL, NULL);

CFDRIVER_DECL(tcagpio, DV_DULL, NULL);

CFDRIVER_DECL(fan53555reg, DV_DULL, NULL);

static const struct cfiattrdata * const rkpmic_attrs[] = { &rkpmiccf_iattrdata, NULL };
CFDRIVER_DECL(rkpmic, DV_DULL, rkpmic_attrs);

static const struct cfiattrdata * const rkreg_attrs[] = { &rkpmiccf_iattrdata, NULL };
CFDRIVER_DECL(rkreg, DV_DULL, rkreg_attrs);

CFDRIVER_DECL(anxedp, DV_DULL, NULL);

static const struct cfiattrdata * const pcaiicmux_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(pcaiicmux, DV_DULL, pcaiicmux_attrs);

CFDRIVER_DECL(es8316ac, DV_DULL, NULL);

CFDRIVER_DECL(cwfg, DV_DULL, NULL);

static const struct cfiattrdata * const spi_attrs[] = { &spicf_iattrdata, NULL };
CFDRIVER_DECL(spi, DV_DULL, spi_attrs);

CFDRIVER_DECL(spiflash, DV_DISK, NULL);

static const struct cfiattrdata * const m25p_attrs[] = { &spiflashbuscf_iattrdata, NULL };
CFDRIVER_DECL(m25p, DV_DULL, m25p_attrs);

CFDRIVER_DECL(irframe, DV_DULL, NULL);

CFDRIVER_DECL(cir, DV_DULL, NULL);

CFDRIVER_DECL(tpm, DV_DULL, NULL);

CFDRIVER_DECL(ld, DV_DISK, NULL);

CFDRIVER_DECL(brgphy, DV_DULL, NULL);

CFDRIVER_DECL(tlphy, DV_DULL, NULL);

CFDRIVER_DECL(nsphy, DV_DULL, NULL);

CFDRIVER_DECL(nsphyter, DV_DULL, NULL);

CFDRIVER_DECL(gentbi, DV_DULL, NULL);

CFDRIVER_DECL(glxtphy, DV_DULL, NULL);

CFDRIVER_DECL(gphyter, DV_DULL, NULL);

CFDRIVER_DECL(inphy, DV_DULL, NULL);

CFDRIVER_DECL(iophy, DV_DULL, NULL);

CFDRIVER_DECL(exphy, DV_DULL, NULL);

CFDRIVER_DECL(lxtphy, DV_DULL, NULL);

CFDRIVER_DECL(makphy, DV_DULL, NULL);

CFDRIVER_DECL(icsphy, DV_DULL, NULL);

CFDRIVER_DECL(igphy, DV_DULL, NULL);

CFDRIVER_DECL(ikphy, DV_DULL, NULL);

CFDRIVER_DECL(sqphy, DV_DULL, NULL);

CFDRIVER_DECL(tqphy, DV_DULL, NULL);

CFDRIVER_DECL(pnaphy, DV_DULL, NULL);

CFDRIVER_DECL(rgephy, DV_DULL, NULL);

CFDRIVER_DECL(urlphy, DV_DULL, NULL);

CFDRIVER_DECL(ukphy, DV_DULL, NULL);

CFDRIVER_DECL(rlphy, DV_DULL, NULL);

CFDRIVER_DECL(atphy, DV_DULL, NULL);

CFDRIVER_DECL(ihphy, DV_DULL, NULL);

CFDRIVER_DECL(rdcphy, DV_DULL, NULL);

CFDRIVER_DECL(smscphy, DV_DULL, NULL);

CFDRIVER_DECL(mcommphy, DV_DULL, NULL);

CFDRIVER_DECL(raid, DV_DISK, NULL);

static const struct cfiattrdata * const mpt_attrs[] = { &scsicf_iattrdata, NULL };
CFDRIVER_DECL(mpt, DV_DULL, mpt_attrs);

static const struct cfiattrdata * const awge_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(awge, DV_IFNET, awge_attrs);

static const struct cfiattrdata * const eqos_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(eqos, DV_IFNET, eqos_attrs);

CFDRIVER_DECL(dwcwdt, DV_DULL, NULL);

static const struct cfiattrdata * const com_attrs[] = { &comcf_iattrdata, NULL };
CFDRIVER_DECL(com, DV_TTY, com_attrs);

static const struct cfiattrdata * const re_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(re, DV_IFNET, re_attrs);

static const struct cfiattrdata * const virtio_attrs[] = { &virtiocf_iattrdata, NULL };
CFDRIVER_DECL(virtio, DV_DULL, virtio_attrs);

CFDRIVER_DECL(vioif, DV_IFNET, NULL);

CFDRIVER_DECL(viornd, DV_DULL, NULL);

static const struct cfiattrdata * const vioscsi_attrs[] = { &scsicf_iattrdata, NULL };
CFDRIVER_DECL(vioscsi, DV_DULL, vioscsi_attrs);

static const struct cfiattrdata * const atabus_attrs[] = { &ata_hlcf_iattrdata, &atapicf_iattrdata, NULL };
CFDRIVER_DECL(atabus, DV_DULL, atabus_attrs);

static const struct cfiattrdata * const ahcisata_attrs[] = { &atacf_iattrdata, NULL };
CFDRIVER_DECL(ahcisata, DV_DULL, ahcisata_attrs);

static const struct cfiattrdata * const siisata_attrs[] = { &atacf_iattrdata, NULL };
CFDRIVER_DECL(siisata, DV_DULL, siisata_attrs);

static const struct cfiattrdata * const dwiic_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(dwiic, DV_DULL, dwiic_attrs);

static const struct cfiattrdata * const applesmc_attrs[] = { &applesmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(applesmc, DV_DULL, applesmc_attrs);

CFDRIVER_DECL(wsdisplay, DV_DULL, NULL);

CFDRIVER_DECL(wskbd, DV_DULL, NULL);

CFDRIVER_DECL(wsmouse, DV_DULL, NULL);

static const struct cfiattrdata * const genfb_attrs[] = { &drmcf_iattrdata, &wsemuldisplaydevcf_iattrdata, NULL };
CFDRIVER_DECL(genfb, DV_DULL, genfb_attrs);

static const struct cfiattrdata * const ohci_attrs[] = { &usbuscf_iattrdata, NULL };
CFDRIVER_DECL(ohci, DV_DULL, ohci_attrs);

static const struct cfiattrdata * const ehci_attrs[] = { &usbuscf_iattrdata, NULL };
CFDRIVER_DECL(ehci, DV_DULL, ehci_attrs);

static const struct cfiattrdata * const xhci_attrs[] = { &usbuscf_iattrdata, NULL };
CFDRIVER_DECL(xhci, DV_DULL, xhci_attrs);

static const struct cfiattrdata * const motg_attrs[] = { &usbuscf_iattrdata, NULL };
CFDRIVER_DECL(motg, DV_DULL, motg_attrs);

static const struct cfiattrdata * const dwctwo_attrs[] = { &usbuscf_iattrdata, NULL };
CFDRIVER_DECL(dwctwo, DV_DULL, dwctwo_attrs);

static const struct cfiattrdata * const sdhc_attrs[] = { &sdmmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(sdhc, DV_DULL, sdhc_attrs);

static const struct cfiattrdata * const dwcmmc_attrs[] = { &sdmmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(dwcmmc, DV_DULL, dwcmmc_attrs);

CFDRIVER_DECL(plrtc, DV_DULL, NULL);

static const struct cfiattrdata * const plgpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(plgpio, DV_DULL, plgpio_attrs);

CFDRIVER_DECL(radio, DV_DULL, NULL);

static const struct cfiattrdata * const nvme_attrs[] = { &nvmecf_iattrdata, NULL };
CFDRIVER_DECL(nvme, DV_DULL, nvme_attrs);

CFDRIVER_DECL(bwfm, DV_IFNET, NULL);

CFDRIVER_DECL(qemufwcfg, DV_DULL, NULL);

CFDRIVER_DECL(amdccp, DV_DULL, NULL);

CFDRIVER_DECL(vnd, DV_DISK, NULL);

CFDRIVER_DECL(cgd, DV_DISK, NULL);

CFDRIVER_DECL(md, DV_DISK, NULL);

CFDRIVER_DECL(fss, DV_DISK, NULL);

CFDRIVER_DECL(tap, DV_IFNET, NULL);

CFDRIVER_DECL(dwhdmi, DV_DULL, NULL);

CFDRIVER_DECL(anxdp, DV_DULL, NULL);

static const struct cfiattrdata * const genet_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(genet, DV_IFNET, genet_attrs);

CFDRIVER_DECL(vmt, DV_DULL, NULL);

static const struct cfiattrdata * const gpio_attrs[] = { &gpiocf_iattrdata, NULL };
CFDRIVER_DECL(gpio, DV_DULL, gpio_attrs);

static const struct cfiattrdata * const pad_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(pad, DV_DULL, pad_attrs);

CFDRIVER_DECL(athn, DV_IFNET, NULL);

static const struct cfiattrdata * const simplebus_attrs[] = { &fdtcf_iattrdata, NULL };
CFDRIVER_DECL(simplebus, DV_DULL, simplebus_attrs);

CFDRIVER_DECL(fregulator, DV_DULL, NULL);

CFDRIVER_DECL(gregulator, DV_DULL, NULL);

CFDRIVER_DECL(pregulator, DV_DULL, NULL);

CFDRIVER_DECL(fclock, DV_DULL, NULL);

CFDRIVER_DECL(ffclock, DV_DULL, NULL);

static const struct cfiattrdata * const gpiokeys_attrs[] = { &wskbddevcf_iattrdata, NULL };
CFDRIVER_DECL(gpiokeys, DV_DULL, gpiokeys_attrs);

CFDRIVER_DECL(gpioleds, DV_DULL, NULL);

CFDRIVER_DECL(panel, DV_DULL, NULL);

CFDRIVER_DECL(dispcon, DV_DULL, NULL);

static const struct cfiattrdata * const iicmux_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(iicmux, DV_DULL, iicmux_attrs);

static const struct cfiattrdata * const cpus_attrs[] = { &fdtcf_iattrdata, NULL };
CFDRIVER_DECL(cpus, DV_DULL, cpus_attrs);

CFDRIVER_DECL(mmcpwrseq, DV_DULL, NULL);

static const struct cfiattrdata * const syscon_attrs[] = { &fdtcf_iattrdata, NULL };
CFDRIVER_DECL(syscon, DV_DULL, syscon_attrs);

CFDRIVER_DECL(pwmbacklight, DV_DULL, NULL);

CFDRIVER_DECL(pwmfan, DV_DULL, NULL);

static const struct cfiattrdata * const ausoc_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(ausoc, DV_DULL, ausoc_attrs);

CFDRIVER_DECL(spdiftx, DV_DULL, NULL);

CFDRIVER_DECL(simpleamp, DV_DULL, NULL);

CFDRIVER_DECL(psci, DV_DULL, NULL);

static const struct cfiattrdata * const cpu_attrs[] = { &cpucf_iattrdata, NULL };
CFDRIVER_DECL(cpu, DV_DULL, cpu_attrs);

CFDRIVER_DECL(wd, DV_DISK, NULL);

static const struct cfiattrdata * const bthub_attrs[] = { &bthubcf_iattrdata, NULL };
CFDRIVER_DECL(bthub, DV_DULL, bthub_attrs);

static const struct cfiattrdata * const pci_attrs[] = { &pcicf_iattrdata, NULL };
CFDRIVER_DECL(pci, DV_DULL, pci_attrs);

CFDRIVER_DECL(aq, DV_IFNET, NULL);

static const struct cfiattrdata * const ppb_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(ppb, DV_DULL, ppb_attrs);

static const struct cfiattrdata * const puc_attrs[] = { &puccf_iattrdata, NULL };
CFDRIVER_DECL(puc, DV_DULL, puc_attrs);

static const struct cfiattrdata * const ixg_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(ixg, DV_IFNET, ixg_attrs);

static const struct cfiattrdata * const ixv_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(ixv, DV_IFNET, ixv_attrs);

static const struct cfiattrdata * const wm_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(wm, DV_IFNET, wm_attrs);

CFDRIVER_DECL(mcx, DV_IFNET, NULL);

static const struct cfiattrdata * const bge_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(bge, DV_IFNET, bge_attrs);

static const struct cfiattrdata * const mskc_attrs[] = { &mskccf_iattrdata, NULL };
CFDRIVER_DECL(mskc, DV_DULL, mskc_attrs);

static const struct cfiattrdata * const msk_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(msk, DV_IFNET, msk_attrs);

static const struct cfiattrdata * const radeon_attrs[] = { &radeonfbbuscf_iattrdata, NULL };
CFDRIVER_DECL(radeon, DV_DULL, radeon_attrs);

static const struct cfiattrdata * const radeondrmkmsfb_attrs[] = { &wsemuldisplaydevcf_iattrdata, &radeonfbbuscf_iattrdata, NULL };
CFDRIVER_DECL(radeondrmkmsfb, DV_DULL, radeondrmkmsfb_attrs);

CFDRIVER_DECL(ena, DV_IFNET, NULL);

CFDRIVER_DECL(vmx, DV_IFNET, NULL);

static const struct cfiattrdata * const rge_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(rge, DV_IFNET, rge_attrs);

static const struct cfiattrdata * const sdmmc_attrs[] = { &sdmmccf_iattrdata, NULL };
CFDRIVER_DECL(sdmmc, DV_DULL, sdmmc_attrs);

static const struct cfiattrdata * const scsibus_attrs[] = { &scsibuscf_iattrdata, NULL };
CFDRIVER_DECL(scsibus, DV_DULL, scsibus_attrs);

static const struct cfiattrdata * const atapibus_attrs[] = { &atapibuscf_iattrdata, NULL };
CFDRIVER_DECL(atapibus, DV_DULL, atapibus_attrs);

CFDRIVER_DECL(cd, DV_DISK, NULL);

CFDRIVER_DECL(sd, DV_DISK, NULL);

CFDRIVER_DECL(st, DV_TAPE, NULL);

CFDRIVER_DECL(ss, DV_DULL, NULL);

CFDRIVER_DECL(uk, DV_DULL, NULL);

static const struct cfiattrdata * const usb_attrs[] = { &usbroothubifcf_iattrdata, NULL };
CFDRIVER_DECL(usb, DV_DULL, usb_attrs);

static const struct cfiattrdata * const uhub_attrs[] = { &usbififcf_iattrdata, &usbdevifcf_iattrdata, NULL };
CFDRIVER_DECL(uhub, DV_DULL, uhub_attrs);

static const struct cfiattrdata * const uaudio_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(uaudio, DV_DULL, uaudio_attrs);

static const struct cfiattrdata * const umidi_attrs[] = { &midibuscf_iattrdata, NULL };
CFDRIVER_DECL(umidi, DV_DULL, umidi_attrs);

CFDRIVER_DECL(ucom, DV_DULL, NULL);

CFDRIVER_DECL(ugen, DV_DULL, NULL);

CFDRIVER_DECL(ugenif, DV_DULL, NULL);

static const struct cfiattrdata * const uhidev_attrs[] = { &uhidbuscf_iattrdata, NULL };
CFDRIVER_DECL(uhidev, DV_DULL, uhidev_attrs);

CFDRIVER_DECL(uhid, DV_DULL, NULL);

static const struct cfiattrdata * const ukbd_attrs[] = { &wskbddevcf_iattrdata, NULL };
CFDRIVER_DECL(ukbd, DV_DULL, ukbd_attrs);

static const struct cfiattrdata * const ums_attrs[] = { &wsmousedevcf_iattrdata, NULL };
CFDRIVER_DECL(ums, DV_DULL, ums_attrs);

static const struct cfiattrdata * const uts_attrs[] = { &wsmousedevcf_iattrdata, NULL };
CFDRIVER_DECL(uts, DV_DULL, uts_attrs);

static const struct cfiattrdata * const uep_attrs[] = { &wsmousedevcf_iattrdata, NULL };
CFDRIVER_DECL(uep, DV_DULL, uep_attrs);

CFDRIVER_DECL(ucycom, DV_DULL, NULL);

CFDRIVER_DECL(ulpt, DV_DULL, NULL);

static const struct cfiattrdata * const umass_attrs[] = { &atapicf_iattrdata, &scsicf_iattrdata, NULL };
CFDRIVER_DECL(umass, DV_DULL, umass_attrs);

static const struct cfiattrdata * const uirda_attrs[] = { &irbuscf_iattrdata, NULL };
CFDRIVER_DECL(uirda, DV_DULL, uirda_attrs);

static const struct cfiattrdata * const stuirda_attrs[] = { &irbuscf_iattrdata, NULL };
CFDRIVER_DECL(stuirda, DV_DULL, stuirda_attrs);

static const struct cfiattrdata * const ustir_attrs[] = { &irbuscf_iattrdata, NULL };
CFDRIVER_DECL(ustir, DV_DULL, ustir_attrs);

static const struct cfiattrdata * const irmce_attrs[] = { &irbuscf_iattrdata, NULL };
CFDRIVER_DECL(irmce, DV_DULL, irmce_attrs);

static const struct cfiattrdata * const ubt_attrs[] = { &btbuscf_iattrdata, NULL };
CFDRIVER_DECL(ubt, DV_DULL, ubt_attrs);

CFDRIVER_DECL(aubtfwl, DV_DULL, NULL);

static const struct cfiattrdata * const pseye_attrs[] = { &videobuscf_iattrdata, NULL };
CFDRIVER_DECL(pseye, DV_DULL, pseye_attrs);

static const struct cfiattrdata * const uvideo_attrs[] = { &videobuscf_iattrdata, NULL };
CFDRIVER_DECL(uvideo, DV_DULL, uvideo_attrs);

static const struct cfiattrdata * const auvitek_attrs[] = { &usbififcf_iattrdata, &i2cbuscf_iattrdata, &dtvbuscf_iattrdata, &videobuscf_iattrdata, NULL };
CFDRIVER_DECL(auvitek, DV_DULL, auvitek_attrs);

static const struct cfiattrdata * const emdtv_attrs[] = { &irbuscf_iattrdata, &dtvbuscf_iattrdata, NULL };
CFDRIVER_DECL(emdtv, DV_DULL, emdtv_attrs);

CFDRIVER_DECL(umodeswitch, DV_DULL, NULL);

CFDRIVER_DECL(uipad, DV_DULL, NULL);

CFDRIVER_DECL(uberry, DV_DULL, NULL);

static const struct cfiattrdata * const uvisor_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uvisor, DV_DULL, uvisor_attrs);

static const struct cfiattrdata * const ugensa_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(ugensa, DV_DULL, ugensa_attrs);

static const struct cfiattrdata * const u3g_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(u3g, DV_DULL, u3g_attrs);

static const struct cfiattrdata * const udsbr_attrs[] = { &radiodevcf_iattrdata, NULL };
CFDRIVER_DECL(udsbr, DV_DULL, udsbr_attrs);

static const struct cfiattrdata * const slurm_attrs[] = { &radiodevcf_iattrdata, NULL };
CFDRIVER_DECL(slurm, DV_DULL, slurm_attrs);

CFDRIVER_DECL(uthum, DV_DULL, NULL);

static const struct cfiattrdata * const aue_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(aue, DV_IFNET, aue_attrs);

CFDRIVER_DECL(cdce, DV_IFNET, NULL);

CFDRIVER_DECL(cue, DV_IFNET, NULL);

CFDRIVER_DECL(kue, DV_IFNET, NULL);

CFDRIVER_DECL(upl, DV_IFNET, NULL);

static const struct cfiattrdata * const url_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(url, DV_IFNET, url_attrs);

static const struct cfiattrdata * const axe_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(axe, DV_IFNET, axe_attrs);

static const struct cfiattrdata * const axen_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(axen, DV_IFNET, axen_attrs);

static const struct cfiattrdata * const mos_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(mos, DV_IFNET, mos_attrs);

static const struct cfiattrdata * const mue_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(mue, DV_IFNET, mue_attrs);

CFDRIVER_DECL(otus, DV_IFNET, NULL);

static const struct cfiattrdata * const udav_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(udav, DV_IFNET, udav_attrs);

static const struct cfiattrdata * const ure_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(ure, DV_IFNET, ure_attrs);

static const struct cfiattrdata * const umodem_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(umodem, DV_DULL, umodem_attrs);

static const struct cfiattrdata * const uftdi_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uftdi, DV_DULL, uftdi_attrs);

static const struct cfiattrdata * const uplcom_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uplcom, DV_DULL, uplcom_attrs);

static const struct cfiattrdata * const umct_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(umct, DV_DULL, umct_attrs);

static const struct cfiattrdata * const umcs_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(umcs, DV_DULL, umcs_attrs);

static const struct cfiattrdata * const uvscom_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uvscom, DV_DULL, uvscom_attrs);

static const struct cfiattrdata * const uxrcom_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uxrcom, DV_DULL, uxrcom_attrs);

static const struct cfiattrdata * const ubsa_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(ubsa, DV_DULL, ubsa_attrs);

static const struct cfiattrdata * const uipaq_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uipaq, DV_DULL, uipaq_attrs);

static const struct cfiattrdata * const ukyopon_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(ukyopon, DV_DULL, ukyopon_attrs);

static const struct cfiattrdata * const uark_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uark, DV_DULL, uark_attrs);

static const struct cfiattrdata * const uslsa_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uslsa, DV_DULL, uslsa_attrs);

static const struct cfiattrdata * const uchcom_attrs[] = { &ucombuscf_iattrdata, NULL };
CFDRIVER_DECL(uchcom, DV_DULL, uchcom_attrs);

static const struct cfiattrdata * const usscanner_attrs[] = { &scsicf_iattrdata, NULL };
CFDRIVER_DECL(usscanner, DV_DULL, usscanner_attrs);

CFDRIVER_DECL(atu, DV_IFNET, NULL);

CFDRIVER_DECL(upgt, DV_IFNET, NULL);

static const struct cfiattrdata * const usmsc_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(usmsc, DV_IFNET, usmsc_attrs);

CFDRIVER_DECL(ural, DV_IFNET, NULL);

CFDRIVER_DECL(rum, DV_IFNET, NULL);

CFDRIVER_DECL(utoppy, DV_DULL, NULL);

CFDRIVER_DECL(zyd, DV_IFNET, NULL);

static const struct cfiattrdata * const udl_attrs[] = { &wsemuldisplaydevcf_iattrdata, NULL };
CFDRIVER_DECL(udl, DV_DULL, udl_attrs);

CFDRIVER_DECL(uhso, DV_IFNET, NULL);

CFDRIVER_DECL(urndis, DV_IFNET, NULL);

CFDRIVER_DECL(urtwn, DV_IFNET, NULL);

CFDRIVER_DECL(urtw, DV_IFNET, NULL);

CFDRIVER_DECL(run, DV_IFNET, NULL);

static const struct cfiattrdata * const udsir_attrs[] = { &irbuscf_iattrdata, NULL };
CFDRIVER_DECL(udsir, DV_DULL, udsir_attrs);

CFDRIVER_DECL(ualea, DV_DULL, NULL);

static const struct cfiattrdata * const plcom_attrs[] = { &plcomcf_iattrdata, NULL };
CFDRIVER_DECL(plcom, DV_TTY, plcom_attrs);

CFDRIVER_DECL(armgic, DV_DULL, NULL);

CFDRIVER_DECL(gicvthree, DV_DULL, NULL);

CFDRIVER_DECL(armgtmr, DV_DULL, NULL);

static const struct cfiattrdata * const armfdt_attrs[] = { &fdtcf_iattrdata, NULL };
CFDRIVER_DECL(armfdt, DV_DULL, armfdt_attrs);

CFDRIVER_DECL(cpufreqdt, DV_DULL, NULL);

static const struct cfiattrdata * const gtmr_attrs[] = { &mpcorebuscf_iattrdata, NULL };
CFDRIVER_DECL(gtmr, DV_DULL, gtmr_attrs);

static const struct cfiattrdata * const gic_attrs[] = { &mpcorebuscf_iattrdata, NULL };
CFDRIVER_DECL(gic, DV_DULL, gic_attrs);

static const struct cfiattrdata * const pcihost_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(pcihost, DV_DULL, pcihost_attrs);

CFDRIVER_DECL(armpmu, DV_DULL, NULL);

static const struct cfiattrdata * const acpifdt_attrs[] = { &acpibuscf_iattrdata, NULL };
CFDRIVER_DECL(acpifdt, DV_DULL, acpifdt_attrs);

static const struct cfiattrdata * const acpi_attrs[] = { &acpiwdrtbuscf_iattrdata, &acpihpetbuscf_iattrdata, &acpimadtbuscf_iattrdata, &acpigtdtbuscf_iattrdata, &acpisdtbuscf_iattrdata, &acpiecdtbuscf_iattrdata, &acpinodebuscf_iattrdata, &acpiapmbuscf_iattrdata, NULL };
CFDRIVER_DECL(acpi, DV_DULL, acpi_attrs);

CFDRIVER_DECL(acpilid, DV_DULL, NULL);

CFDRIVER_DECL(acpibut, DV_DULL, NULL);

CFDRIVER_DECL(acpiacad, DV_DULL, NULL);

CFDRIVER_DECL(acpibat, DV_DULL, NULL);

CFDRIVER_DECL(acpifan, DV_DULL, NULL);

CFDRIVER_DECL(acpiged, DV_DULL, NULL);

CFDRIVER_DECL(acpitz, DV_DULL, NULL);

CFDRIVER_DECL(acpipcd, DV_DULL, NULL);

CFDRIVER_DECL(acpipcc, DV_DULL, NULL);

CFDRIVER_DECL(acpicppc, DV_DULL, NULL);

static const struct cfiattrdata * const nxpiic_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(nxpiic, DV_DULL, nxpiic_attrs);

CFDRIVER_DECL(sbsawdt, DV_DULL, NULL);

static const struct cfiattrdata * const acpipchb_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(acpipchb, DV_DULL, acpipchb_attrs);

CFDRIVER_DECL(gxbbclkc, DV_DULL, NULL);

CFDRIVER_DECL(gxbbaoclkc, DV_DULL, NULL);

CFDRIVER_DECL(g12clkc, DV_DULL, NULL);

CFDRIVER_DECL(g12aoclkc, DV_DULL, NULL);

CFDRIVER_DECL(mesonresets, DV_DULL, NULL);

CFDRIVER_DECL(mesonuart, DV_DULL, NULL);

static const struct cfiattrdata * const mesonpinctrl_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(mesonpinctrl, DV_DULL, mesonpinctrl_attrs);

static const struct cfiattrdata * const mesongxmmc_attrs[] = { &sdmmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(mesongxmmc, DV_DULL, mesongxmmc_attrs);

CFDRIVER_DECL(mesonusbphy, DV_DULL, NULL);

CFDRIVER_DECL(mesongxlu2phy, DV_DULL, NULL);

CFDRIVER_DECL(mesongxlu3phy, DV_DULL, NULL);

CFDRIVER_DECL(mesong12u2phy, DV_DULL, NULL);

CFDRIVER_DECL(mesong12u3pphy, DV_DULL, NULL);

CFDRIVER_DECL(mesonusbctrl, DV_DULL, NULL);

CFDRIVER_DECL(mesonrng, DV_DULL, NULL);

CFDRIVER_DECL(gxlphy, DV_DULL, NULL);

CFDRIVER_DECL(mesongxwdt, DV_DULL, NULL);

CFDRIVER_DECL(mesonpwm, DV_DULL, NULL);

CFDRIVER_DECL(mesonthermal, DV_DULL, NULL);

CFDRIVER_DECL(appledart, DV_DULL, NULL);

static const struct cfiattrdata * const appleiic_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(appleiic, DV_DULL, appleiic_attrs);

CFDRIVER_DECL(appleintc, DV_DULL, NULL);

CFDRIVER_DECL(applembox, DV_DULL, NULL);

static const struct cfiattrdata * const applepcie_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(applepcie, DV_DULL, applepcie_attrs);

CFDRIVER_DECL(applepinctrl, DV_DULL, NULL);

CFDRIVER_DECL(applepmgr, DV_DULL, NULL);

CFDRIVER_DECL(applewdog, DV_DULL, NULL);

CFDRIVER_DECL(bcmicu, DV_DULL, NULL);

static const struct cfiattrdata * const bcmmbox_attrs[] = { &bcmmboxbuscf_iattrdata, NULL };
CFDRIVER_DECL(bcmmbox, DV_DULL, bcmmbox_attrs);

CFDRIVER_DECL(bcmpmwdog, DV_DULL, NULL);

CFDRIVER_DECL(bcmrng, DV_DULL, NULL);

CFDRIVER_DECL(bcmaux, DV_DULL, NULL);

static const struct cfiattrdata * const bcmsdhost_attrs[] = { &sdmmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(bcmsdhost, DV_DULL, bcmsdhost_attrs);

CFDRIVER_DECL(bcmdmac, DV_DULL, NULL);

static const struct cfiattrdata * const bcmspi_attrs[] = { &spibuscf_iattrdata, NULL };
CFDRIVER_DECL(bcmspi, DV_DULL, bcmspi_attrs);

static const struct cfiattrdata * const bsciic_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(bsciic, DV_DULL, bsciic_attrs);

static const struct cfiattrdata * const vchiq_attrs[] = { &vchiqbuscf_iattrdata, NULL };
CFDRIVER_DECL(vchiq, DV_DULL, vchiq_attrs);

static const struct cfiattrdata * const vcaudio_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(vcaudio, DV_DULL, vcaudio_attrs);

static const struct cfiattrdata * const bcmgpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(bcmgpio, DV_DULL, bcmgpio_attrs);

CFDRIVER_DECL(bcmcprman, DV_DULL, NULL);

CFDRIVER_DECL(vcmbox, DV_DULL, NULL);

CFDRIVER_DECL(tegralic, DV_DULL, NULL);

CFDRIVER_DECL(tegramc, DV_DULL, NULL);

CFDRIVER_DECL(tegrapmc, DV_DULL, NULL);

CFDRIVER_DECL(tegrafuse, DV_DULL, NULL);

CFDRIVER_DECL(tegra210car, DV_DULL, NULL);

static const struct cfiattrdata * const tegragpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(tegragpio, DV_DULL, tegragpio_attrs);

CFDRIVER_DECL(tegratimer, DV_DULL, NULL);

CFDRIVER_DECL(tegrapinmux, DV_DULL, NULL);

CFDRIVER_DECL(tegraapbdma, DV_DULL, NULL);

static const struct cfiattrdata * const tegra210xpad_attrs[] = { &tegra210xpadcf_iattrdata, NULL };
CFDRIVER_DECL(tegra210xpad, DV_DULL, tegra210xpad_attrs);

static const struct cfiattrdata * const tegra210xphy_attrs[] = { &tegra210xpadcf_iattrdata, NULL };
CFDRIVER_DECL(tegra210xphy, DV_DULL, tegra210xphy_attrs);

static const struct cfiattrdata * const tegrai2c_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(tegrai2c, DV_DULL, tegrai2c_attrs);

CFDRIVER_DECL(tegrartc, DV_DULL, NULL);

CFDRIVER_DECL(tegrausbphy, DV_DULL, NULL);

CFDRIVER_DECL(tegrasoctherm, DV_DULL, NULL);

static const struct cfiattrdata * const tegrapcie_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(tegrapcie, DV_DULL, tegrapcie_attrs);

static const struct cfiattrdata * const tegracec_attrs[] = { &hdmicecbuscf_iattrdata, NULL };
CFDRIVER_DECL(tegracec, DV_DULL, tegracec_attrs);

CFDRIVER_DECL(imx8mqccm, DV_DULL, NULL);

CFDRIVER_DECL(imx7gpc, DV_DULL, NULL);

CFDRIVER_DECL(imxiomux, DV_DULL, NULL);

static const struct cfiattrdata * const imxgpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(imxgpio, DV_DULL, imxgpio_attrs);

CFDRIVER_DECL(imxuart, DV_TTY, NULL);

static const struct cfiattrdata * const enet_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(enet, DV_IFNET, enet_attrs);

CFDRIVER_DECL(imx8mqusbphy, DV_DULL, NULL);

static const struct cfiattrdata * const imxi2c_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(imxi2c, DV_DULL, imxi2c_attrs);

CFDRIVER_DECL(rkcru, DV_DULL, NULL);

static const struct cfiattrdata * const rkiomux_attrs[] = { &rkiomuxcf_iattrdata, NULL };
CFDRIVER_DECL(rkiomux, DV_DULL, rkiomux_attrs);

static const struct cfiattrdata * const rkgpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(rkgpio, DV_DULL, rkgpio_attrs);

static const struct cfiattrdata * const rkiic_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(rkiic, DV_DULL, rkiic_attrs);

static const struct cfiattrdata * const rkspi_attrs[] = { &spibuscf_iattrdata, NULL };
CFDRIVER_DECL(rkspi, DV_DULL, rkspi_attrs);

static const struct cfiattrdata * const rkusb_attrs[] = { &rkusbcf_iattrdata, NULL };
CFDRIVER_DECL(rkusb, DV_DULL, rkusb_attrs);

CFDRIVER_DECL(rkusbphy, DV_DULL, NULL);

CFDRIVER_DECL(rkpciephy, DV_DULL, NULL);

static const struct cfiattrdata * const rkpcie_attrs[] = { &pcibuscf_iattrdata, NULL };
CFDRIVER_DECL(rkpcie, DV_DULL, rkpcie_attrs);

CFDRIVER_DECL(rkemmcphy, DV_DULL, NULL);

CFDRIVER_DECL(rktsadc, DV_DULL, NULL);

CFDRIVER_DECL(rkpwm, DV_DULL, NULL);

static const struct cfiattrdata * const rkdrm_attrs[] = { &rkfbbuscf_iattrdata, NULL };
CFDRIVER_DECL(rkdrm, DV_DULL, rkdrm_attrs);

static const struct cfiattrdata * const rkfb_attrs[] = { &wsemuldisplaydevcf_iattrdata, &rkfbbuscf_iattrdata, NULL };
CFDRIVER_DECL(rkfb, DV_DULL, rkfb_attrs);

CFDRIVER_DECL(rkvop, DV_DULL, NULL);

CFDRIVER_DECL(rki2s, DV_DULL, NULL);

CFDRIVER_DECL(rkv1crypto, DV_DULL, NULL);

CFDRIVER_DECL(exuart, DV_DULL, NULL);

CFDRIVER_DECL(sun8ih3ccu, DV_DULL, NULL);

CFDRIVER_DECL(sun8ih3rccu, DV_DULL, NULL);

CFDRIVER_DECL(sun50ia64ccu, DV_DULL, NULL);

CFDRIVER_DECL(sun50ia64rccu, DV_DULL, NULL);

CFDRIVER_DECL(sun50ih6ccu, DV_DULL, NULL);

CFDRIVER_DECL(sun50ih6rccu, DV_DULL, NULL);

CFDRIVER_DECL(sunxiresets, DV_DULL, NULL);

CFDRIVER_DECL(sunxigates, DV_DULL, NULL);

CFDRIVER_DECL(sunxigmacclk, DV_DULL, NULL);

CFDRIVER_DECL(sunxinmi, DV_DULL, NULL);

static const struct cfiattrdata * const sunxigpio_attrs[] = { &gpiobuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxigpio, DV_DULL, sunxigpio_attrs);

CFDRIVER_DECL(sunxipwm, DV_DULL, NULL);

static const struct cfiattrdata * const sunximmc_attrs[] = { &sdmmcbuscf_iattrdata, NULL };
CFDRIVER_DECL(sunximmc, DV_DULL, sunximmc_attrs);

CFDRIVER_DECL(sunxiusbphy, DV_DULL, NULL);

CFDRIVER_DECL(sunxiusb3phy, DV_DULL, NULL);

static const struct cfiattrdata * const sunxitwi_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxitwi, DV_DULL, sunxitwi_attrs);

static const struct cfiattrdata * const sunxirsb_attrs[] = { &i2cbuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxirsb, DV_DULL, sunxirsb_attrs);

CFDRIVER_DECL(sunxirtc, DV_DULL, NULL);

static const struct cfiattrdata * const emac_attrs[] = { &miicf_iattrdata, NULL };
CFDRIVER_DECL(emac, DV_IFNET, emac_attrs);

CFDRIVER_DECL(sunxiwdt, DV_DULL, NULL);

CFDRIVER_DECL(sun6idma, DV_DULL, NULL);

static const struct cfiattrdata * const sunxicodec_attrs[] = { &audiobuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxicodec, DV_DULL, sunxicodec_attrs);

CFDRIVER_DECL(sun8icodec, DV_DULL, NULL);

CFDRIVER_DECL(h3codec, DV_DULL, NULL);

CFDRIVER_DECL(a64acodec, DV_DULL, NULL);

CFDRIVER_DECL(sunxii2s, DV_DULL, NULL);

CFDRIVER_DECL(sunxisid, DV_DULL, NULL);

CFDRIVER_DECL(sunxithermal, DV_DULL, NULL);

CFDRIVER_DECL(sunxisramc, DV_DULL, NULL);

static const struct cfiattrdata * const sun6ispi_attrs[] = { &spibuscf_iattrdata, NULL };
CFDRIVER_DECL(sun6ispi, DV_DULL, sun6ispi_attrs);

static const struct cfiattrdata * const sunxide2bus_attrs[] = { &sunxide2buscf_iattrdata, &fdtcf_iattrdata, NULL };
CFDRIVER_DECL(sunxide2bus, DV_DULL, sunxide2bus_attrs);

CFDRIVER_DECL(sunxide2ccu, DV_DULL, NULL);

CFDRIVER_DECL(sunximixer, DV_DULL, NULL);

CFDRIVER_DECL(sunxilcdc, DV_DULL, NULL);

static const struct cfiattrdata * const sunxidrm_attrs[] = { &sunxifbbuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxidrm, DV_DULL, sunxidrm_attrs);

static const struct cfiattrdata * const sunxifb_attrs[] = { &wsemuldisplaydevcf_iattrdata, &sunxifbbuscf_iattrdata, NULL };
CFDRIVER_DECL(sunxifb, DV_DULL, sunxifb_attrs);

CFDRIVER_DECL(sunxihdmiphy, DV_DULL, NULL);

CFDRIVER_DECL(sun8icrypto, DV_DULL, NULL);


struct cfdriver * const cfdriver_list_initial[] = {
	&swwdog_cd,
	&spkr_cd,
	&audio_cd,
	&midi_cd,
	&hdaudio_cd,
	&hdafg_cd,
	&video_cd,
	&dtv_cd,
	&hdmicec_cd,
	&spdmem_cd,
	&iic_cd,
	&pcf8563rtc_cd,
	&seeprom_cd,
	&dsrtc_cd,
	&axppmic_cd,
	&axpreg_cd,
	&titemp_cd,
	&as3722pmic_cd,
	&as3722reg_cd,
	&max77620pmic_cd,
	&tcagpio_cd,
	&fan53555reg_cd,
	&rkpmic_cd,
	&rkreg_cd,
	&anxedp_cd,
	&pcaiicmux_cd,
	&es8316ac_cd,
	&cwfg_cd,
	&spi_cd,
	&spiflash_cd,
	&m25p_cd,
	&irframe_cd,
	&cir_cd,
	&tpm_cd,
	&ld_cd,
	&brgphy_cd,
	&tlphy_cd,
	&nsphy_cd,
	&nsphyter_cd,
	&gentbi_cd,
	&glxtphy_cd,
	&gphyter_cd,
	&inphy_cd,
	&iophy_cd,
	&exphy_cd,
	&lxtphy_cd,
	&makphy_cd,
	&icsphy_cd,
	&igphy_cd,
	&ikphy_cd,
	&sqphy_cd,
	&tqphy_cd,
	&pnaphy_cd,
	&rgephy_cd,
	&urlphy_cd,
	&ukphy_cd,
	&rlphy_cd,
	&atphy_cd,
	&ihphy_cd,
	&rdcphy_cd,
	&smscphy_cd,
	&mcommphy_cd,
	&raid_cd,
	&mpt_cd,
	&awge_cd,
	&eqos_cd,
	&dwcwdt_cd,
	&com_cd,
	&re_cd,
	&virtio_cd,
	&vioif_cd,
	&viornd_cd,
	&vioscsi_cd,
	&atabus_cd,
	&ahcisata_cd,
	&siisata_cd,
	&dwiic_cd,
	&applesmc_cd,
	&wsdisplay_cd,
	&wskbd_cd,
	&wsmouse_cd,
	&genfb_cd,
	&ohci_cd,
	&ehci_cd,
	&xhci_cd,
	&motg_cd,
	&dwctwo_cd,
	&sdhc_cd,
	&dwcmmc_cd,
	&plrtc_cd,
	&plgpio_cd,
	&radio_cd,
	&nvme_cd,
	&bwfm_cd,
	&qemufwcfg_cd,
	&amdccp_cd,
	&vnd_cd,
	&cgd_cd,
	&md_cd,
	&fss_cd,
	&tap_cd,
	&dwhdmi_cd,
	&anxdp_cd,
	&genet_cd,
	&vmt_cd,
	&gpio_cd,
	&pad_cd,
	&athn_cd,
	&simplebus_cd,
	&fregulator_cd,
	&gregulator_cd,
	&pregulator_cd,
	&fclock_cd,
	&ffclock_cd,
	&gpiokeys_cd,
	&gpioleds_cd,
	&panel_cd,
	&dispcon_cd,
	&iicmux_cd,
	&cpus_cd,
	&mmcpwrseq_cd,
	&syscon_cd,
	&pwmbacklight_cd,
	&pwmfan_cd,
	&ausoc_cd,
	&spdiftx_cd,
	&simpleamp_cd,
	&psci_cd,
	&cpu_cd,
	&wd_cd,
	&bthub_cd,
	&pci_cd,
	&aq_cd,
	&ppb_cd,
	&puc_cd,
	&ixg_cd,
	&ixv_cd,
	&wm_cd,
	&mcx_cd,
	&bge_cd,
	&mskc_cd,
	&msk_cd,
	&radeon_cd,
	&radeondrmkmsfb_cd,
	&ena_cd,
	&vmx_cd,
	&rge_cd,
	&sdmmc_cd,
	&scsibus_cd,
	&atapibus_cd,
	&cd_cd,
	&sd_cd,
	&st_cd,
	&ss_cd,
	&uk_cd,
	&usb_cd,
	&uhub_cd,
	&uaudio_cd,
	&umidi_cd,
	&ucom_cd,
	&ugen_cd,
	&ugenif_cd,
	&uhidev_cd,
	&uhid_cd,
	&ukbd_cd,
	&ums_cd,
	&uts_cd,
	&uep_cd,
	&ucycom_cd,
	&ulpt_cd,
	&umass_cd,
	&uirda_cd,
	&stuirda_cd,
	&ustir_cd,
	&irmce_cd,
	&ubt_cd,
	&aubtfwl_cd,
	&pseye_cd,
	&uvideo_cd,
	&auvitek_cd,
	&emdtv_cd,
	&umodeswitch_cd,
	&uipad_cd,
	&uberry_cd,
	&uvisor_cd,
	&ugensa_cd,
	&u3g_cd,
	&udsbr_cd,
	&slurm_cd,
	&uthum_cd,
	&aue_cd,
	&cdce_cd,
	&cue_cd,
	&kue_cd,
	&upl_cd,
	&url_cd,
	&axe_cd,
	&axen_cd,
	&mos_cd,
	&mue_cd,
	&otus_cd,
	&udav_cd,
	&ure_cd,
	&umodem_cd,
	&uftdi_cd,
	&uplcom_cd,
	&umct_cd,
	&umcs_cd,
	&uvscom_cd,
	&uxrcom_cd,
	&ubsa_cd,
	&uipaq_cd,
	&ukyopon_cd,
	&uark_cd,
	&uslsa_cd,
	&uchcom_cd,
	&usscanner_cd,
	&atu_cd,
	&upgt_cd,
	&usmsc_cd,
	&ural_cd,
	&rum_cd,
	&utoppy_cd,
	&zyd_cd,
	&udl_cd,
	&uhso_cd,
	&urndis_cd,
	&urtwn_cd,
	&urtw_cd,
	&run_cd,
	&udsir_cd,
	&ualea_cd,
	&plcom_cd,
	&armgic_cd,
	&gicvthree_cd,
	&armgtmr_cd,
	&armfdt_cd,
	&cpufreqdt_cd,
	&gtmr_cd,
	&gic_cd,
	&pcihost_cd,
	&armpmu_cd,
	&acpifdt_cd,
	&acpi_cd,
	&acpilid_cd,
	&acpibut_cd,
	&acpiacad_cd,
	&acpibat_cd,
	&acpifan_cd,
	&acpiged_cd,
	&acpitz_cd,
	&acpipcd_cd,
	&acpipcc_cd,
	&acpicppc_cd,
	&nxpiic_cd,
	&sbsawdt_cd,
	&acpipchb_cd,
	&gxbbclkc_cd,
	&gxbbaoclkc_cd,
	&g12clkc_cd,
	&g12aoclkc_cd,
	&mesonresets_cd,
	&mesonuart_cd,
	&mesonpinctrl_cd,
	&mesongxmmc_cd,
	&mesonusbphy_cd,
	&mesongxlu2phy_cd,
	&mesongxlu3phy_cd,
	&mesong12u2phy_cd,
	&mesong12u3pphy_cd,
	&mesonusbctrl_cd,
	&mesonrng_cd,
	&gxlphy_cd,
	&mesongxwdt_cd,
	&mesonpwm_cd,
	&mesonthermal_cd,
	&appledart_cd,
	&appleiic_cd,
	&appleintc_cd,
	&applembox_cd,
	&applepcie_cd,
	&applepinctrl_cd,
	&applepmgr_cd,
	&applewdog_cd,
	&bcmicu_cd,
	&bcmmbox_cd,
	&bcmpmwdog_cd,
	&bcmrng_cd,
	&bcmaux_cd,
	&bcmsdhost_cd,
	&bcmdmac_cd,
	&bcmspi_cd,
	&bsciic_cd,
	&vchiq_cd,
	&vcaudio_cd,
	&bcmgpio_cd,
	&bcmcprman_cd,
	&vcmbox_cd,
	&tegralic_cd,
	&tegramc_cd,
	&tegrapmc_cd,
	&tegrafuse_cd,
	&tegra210car_cd,
	&tegragpio_cd,
	&tegratimer_cd,
	&tegrapinmux_cd,
	&tegraapbdma_cd,
	&tegra210xpad_cd,
	&tegra210xphy_cd,
	&tegrai2c_cd,
	&tegrartc_cd,
	&tegrausbphy_cd,
	&tegrasoctherm_cd,
	&tegrapcie_cd,
	&tegracec_cd,
	&imx8mqccm_cd,
	&imx7gpc_cd,
	&imxiomux_cd,
	&imxgpio_cd,
	&imxuart_cd,
	&enet_cd,
	&imx8mqusbphy_cd,
	&imxi2c_cd,
	&rkcru_cd,
	&rkiomux_cd,
	&rkgpio_cd,
	&rkiic_cd,
	&rkspi_cd,
	&rkusb_cd,
	&rkusbphy_cd,
	&rkpciephy_cd,
	&rkpcie_cd,
	&rkemmcphy_cd,
	&rktsadc_cd,
	&rkpwm_cd,
	&rkdrm_cd,
	&rkfb_cd,
	&rkvop_cd,
	&rki2s_cd,
	&rkv1crypto_cd,
	&exuart_cd,
	&sun8ih3ccu_cd,
	&sun8ih3rccu_cd,
	&sun50ia64ccu_cd,
	&sun50ia64rccu_cd,
	&sun50ih6ccu_cd,
	&sun50ih6rccu_cd,
	&sunxiresets_cd,
	&sunxigates_cd,
	&sunxigmacclk_cd,
	&sunxinmi_cd,
	&sunxigpio_cd,
	&sunxipwm_cd,
	&sunximmc_cd,
	&sunxiusbphy_cd,
	&sunxiusb3phy_cd,
	&sunxitwi_cd,
	&sunxirsb_cd,
	&sunxirtc_cd,
	&emac_cd,
	&sunxiwdt_cd,
	&sun6idma_cd,
	&sunxicodec_cd,
	&sun8icodec_cd,
	&h3codec_cd,
	&a64acodec_cd,
	&sunxii2s_cd,
	&sunxisid_cd,
	&sunxithermal_cd,
	&sunxisramc_cd,
	&sun6ispi_cd,
	&sunxide2bus_cd,
	&sunxide2ccu_cd,
	&sunximixer_cd,
	&sunxilcdc_cd,
	&sunxidrm_cd,
	&sunxifb_cd,
	&sunxihdmiphy_cd,
	&sun8icrypto_cd,
	NULL
};

extern struct cfattach audio_ca;
extern struct cfattach midi_ca;
extern struct cfattach spkr_audio_ca;
extern struct cfattach hdafg_ca;
extern struct cfattach video_ca;
extern struct cfattach dtv_ca;
extern struct cfattach hdmicec_ca;
extern struct cfattach iic_ca;
extern struct cfattach pcf8563rtc_ca;
extern struct cfattach seeprom_ca;
extern struct cfattach dsrtc_ca;
extern struct cfattach spdmem_iic_ca;
extern struct cfattach axppmic_ca;
extern struct cfattach axpreg_ca;
extern struct cfattach titemp_ca;
extern struct cfattach as3722pmic_ca;
extern struct cfattach as3722reg_ca;
extern struct cfattach max77620pmic_ca;
extern struct cfattach tcagpio_ca;
extern struct cfattach fan53555reg_ca;
extern struct cfattach rkpmic_ca;
extern struct cfattach rkreg_ca;
extern struct cfattach anxedp_ca;
extern struct cfattach pcaiicmux_ca;
extern struct cfattach es8316ac_ca;
extern struct cfattach cwfg_ca;
extern struct cfattach spi_ca;
extern struct cfattach spiflash_ca;
extern struct cfattach m25p_ca;
extern struct cfattach irframe_ca;
extern struct cfattach cir_ca;
extern struct cfattach brgphy_ca;
extern struct cfattach tlphy_ca;
extern struct cfattach nsphy_ca;
extern struct cfattach nsphyter_ca;
extern struct cfattach gentbi_ca;
extern struct cfattach glxtphy_ca;
extern struct cfattach gphyter_ca;
extern struct cfattach inphy_ca;
extern struct cfattach iophy_ca;
extern struct cfattach exphy_ca;
extern struct cfattach lxtphy_ca;
extern struct cfattach makphy_ca;
extern struct cfattach icsphy_ca;
extern struct cfattach igphy_ca;
extern struct cfattach ikphy_ca;
extern struct cfattach sqphy_ca;
extern struct cfattach tqphy_ca;
extern struct cfattach pnaphy_ca;
extern struct cfattach rgephy_ca;
extern struct cfattach urlphy_ca;
extern struct cfattach ukphy_ca;
extern struct cfattach rlphy_ca;
extern struct cfattach atphy_ca;
extern struct cfattach ihphy_ca;
extern struct cfattach rdcphy_ca;
extern struct cfattach smscphy_ca;
extern struct cfattach mcommphy_ca;
extern struct cfattach ld_virtio_ca;
extern struct cfattach vioif_ca;
extern struct cfattach viornd_ca;
extern struct cfattach vioscsi_ca;
extern struct cfattach atabus_ca;
extern struct cfattach wsdisplay_emul_ca;
extern struct cfattach wskbd_ca;
extern struct cfattach wsmouse_ca;
extern struct cfattach radio_ca;
extern struct cfattach ld_nvme_ca;
extern struct cfattach gpio_ca;
extern struct cfattach simplebus_ca;
extern struct cfattach fregulator_ca;
extern struct cfattach gregulator_ca;
extern struct cfattach pregulator_ca;
extern struct cfattach fclock_ca;
extern struct cfattach ffclock_ca;
extern struct cfattach gpiokeys_ca;
extern struct cfattach gpioleds_ca;
extern struct cfattach fdt_panel_ca;
extern struct cfattach panel_fdt_ca;
extern struct cfattach dispcon_hdmi_ca;
extern struct cfattach iicmux_fdt_ca;
extern struct cfattach cpus_ca;
extern struct cfattach mmcpwrseq_simple_ca;
extern struct cfattach mmcpwrseq_emmc_ca;
extern struct cfattach syscon_ca;
extern struct cfattach pwmbacklight_ca;
extern struct cfattach pwmfan_ca;
extern struct cfattach ausoc_ca;
extern struct cfattach spdiftx_ca;
extern struct cfattach simplefb_ca;
extern struct cfattach ns8250_uart_ca;
extern struct cfattach dw_apb_uart_ca;
extern struct cfattach ehci_fdt_ca;
extern struct cfattach ohci_fdt_ca;
extern struct cfattach dwc2_fdt_ca;
extern struct cfattach dwc3_fdt_ca;
extern struct cfattach dwcmmc_fdt_ca;
extern struct cfattach dwcwdt_fdt_ca;
extern struct cfattach virtio_mmio_fdt_ca;
extern struct cfattach qemufwcfg_fdt_ca;
extern struct cfattach plgpio_fdt_ca;
extern struct cfattach ahcisata_fdt_ca;
extern struct cfattach dwiic_fdt_ca;
extern struct cfattach amdccp_fdt_ca;
extern struct cfattach arasan_sdhc_fdt_ca;
extern struct cfattach simpleamp_ca;
extern struct cfattach genet_fdt_ca;
extern struct cfattach vmt_fdt_ca;
extern struct cfattach wd_ca;
extern struct cfattach bthub_ca;
extern struct cfattach pci_ca;
extern struct cfattach mpt_pci_ca;
extern struct cfattach aq_ca;
extern struct cfattach ahcisata_pci_ca;
extern struct cfattach ppb_ca;
extern struct cfattach puc_ca;
extern struct cfattach com_puc_ca;
extern struct cfattach ohci_pci_ca;
extern struct cfattach ehci_pci_ca;
extern struct cfattach xhci_pci_ca;
extern struct cfattach ixg_ca;
extern struct cfattach ixv_ca;
extern struct cfattach wm_ca;
extern struct cfattach mcx_ca;
extern struct cfattach bge_ca;
extern struct cfattach re_pci_ca;
extern struct cfattach mskc_ca;
extern struct cfattach msk_ca;
extern struct cfattach siisata_pci_ca;
extern struct cfattach hdaudio_pci_ca;
extern struct cfattach virtio_pci_ca;
extern struct cfattach nvme_pci_ca;
extern struct cfattach radeon_ca;
extern struct cfattach radeondrmkmsfb_ca;
extern struct cfattach ena_ca;
extern struct cfattach vmx_ca;
extern struct cfattach rge_ca;
extern struct cfattach sdmmc_ca;
extern struct cfattach ld_sdmmc_ca;
extern struct cfattach bwfm_sdio_ca;
extern struct cfattach scsibus_ca;
extern struct cfattach atapibus_ca;
extern struct cfattach cd_ca;
extern struct cfattach sd_ca;
extern struct cfattach st_scsibus_ca;
extern struct cfattach st_atapibus_ca;
extern struct cfattach ss_ca;
extern struct cfattach uk_ca;
extern struct cfattach usb_ca;
extern struct cfattach uroothub_ca;
extern struct cfattach uhub_ca;
extern struct cfattach uaudio_ca;
extern struct cfattach umidi_ca;
extern struct cfattach ucom_ca;
extern struct cfattach ugen_ca;
extern struct cfattach ugenif_ca;
extern struct cfattach uhidev_ca;
extern struct cfattach uhid_ca;
extern struct cfattach ukbd_ca;
extern struct cfattach ums_ca;
extern struct cfattach uts_ca;
extern struct cfattach uep_ca;
extern struct cfattach ucycom_ca;
extern struct cfattach ulpt_ca;
extern struct cfattach umass_ca;
extern struct cfattach uirda_ca;
extern struct cfattach stuirda_ca;
extern struct cfattach ustir_ca;
extern struct cfattach irmce_ca;
extern struct cfattach ubt_ca;
extern struct cfattach aubtfwl_ca;
extern struct cfattach pseye_ca;
extern struct cfattach uvideo_ca;
extern struct cfattach auvitek_ca;
extern struct cfattach emdtv_ca;
extern struct cfattach umodeswitch_ca;
extern struct cfattach uipad_ca;
extern struct cfattach uberry_ca;
extern struct cfattach uvisor_ca;
extern struct cfattach ugensa_ca;
extern struct cfattach u3g_ca;
extern struct cfattach udsbr_ca;
extern struct cfattach slurm_ca;
extern struct cfattach uthum_ca;
extern struct cfattach aue_ca;
extern struct cfattach cdce_ca;
extern struct cfattach cue_ca;
extern struct cfattach kue_ca;
extern struct cfattach upl_ca;
extern struct cfattach url_ca;
extern struct cfattach axe_ca;
extern struct cfattach axen_ca;
extern struct cfattach mos_ca;
extern struct cfattach mue_ca;
extern struct cfattach otus_ca;
extern struct cfattach udav_ca;
extern struct cfattach ure_ca;
extern struct cfattach umodem_ca;
extern struct cfattach uftdi_ca;
extern struct cfattach uplcom_ca;
extern struct cfattach umct_ca;
extern struct cfattach umcs_ca;
extern struct cfattach uvscom_ca;
extern struct cfattach uxrcom_ca;
extern struct cfattach ubsa_ca;
extern struct cfattach uipaq_ca;
extern struct cfattach ukyopon_ca;
extern struct cfattach uark_ca;
extern struct cfattach uslsa_ca;
extern struct cfattach uchcom_ca;
extern struct cfattach usscanner_ca;
extern struct cfattach atu_ca;
extern struct cfattach upgt_ca;
extern struct cfattach usmsc_ca;
extern struct cfattach ural_ca;
extern struct cfattach rum_ca;
extern struct cfattach utoppy_ca;
extern struct cfattach zyd_ca;
extern struct cfattach udl_ca;
extern struct cfattach uhso_ca;
extern struct cfattach urndis_ca;
extern struct cfattach urtwn_ca;
extern struct cfattach urtw_ca;
extern struct cfattach run_ca;
extern struct cfattach athn_usb_ca;
extern struct cfattach udsir_ca;
extern struct cfattach ualea_ca;
extern struct cfattach bwfm_usb_ca;
extern struct cfattach armgic_ca;
extern struct cfattach armgtmr_ca;
extern struct cfattach arm_fdt_ca;
extern struct cfattach cpu_fdt_ca;
extern struct cfattach cpufreq_dt_ca;
extern struct cfattach gtmr_fdt_ca;
extern struct cfattach gic_fdt_ca;
extern struct cfattach gicv3_fdt_ca;
extern struct cfattach plcom_fdt_ca;
extern struct cfattach plrtc_fdt_ca;
extern struct cfattach psci_fdt_ca;
extern struct cfattach pcihost_fdt_ca;
extern struct cfattach pmu_fdt_ca;
extern struct cfattach plfb_fdt_ca;
extern struct cfattach acpi_fdt_ca;
extern struct cfattach acpi_ca;
extern struct cfattach acpilid_ca;
extern struct cfattach acpibut_ca;
extern struct cfattach acpiacad_ca;
extern struct cfattach acpibat_ca;
extern struct cfattach acpifan_ca;
extern struct cfattach acpiged_ca;
extern struct cfattach acpitz_ca;
extern struct cfattach acpipcd_ca;
extern struct cfattach acpipcc_ca;
extern struct cfattach acpicppc_ca;
extern struct cfattach com_acpi_ca;
extern struct cfattach tpm_acpi_ca;
extern struct cfattach sdhc_acpi_ca;
extern struct cfattach qemufwcfg_acpi_ca;
extern struct cfattach ahcisata_acpi_ca;
extern struct cfattach plgpio_acpi_ca;
extern struct cfattach dwiic_acpi_ca;
extern struct cfattach nxpiic_acpi_ca;
extern struct cfattach amdccp_acpi_ca;
extern struct cfattach virtio_acpi_ca;
extern struct cfattach ohci_acpi_ca;
extern struct cfattach ehci_acpi_ca;
extern struct cfattach xhci_acpi_ca;
extern struct cfattach genet_acpi_ca;
extern struct cfattach eqos_acpi_ca;
extern struct cfattach dwcmmc_acpi_ca;
extern struct cfattach dwcwdt_acpi_ca;
extern struct cfattach cpu_acpi_ca;
extern struct cfattach gic_acpi_ca;
extern struct cfattach gicv3_acpi_ca;
extern struct cfattach gtmr_acpi_ca;
extern struct cfattach sbsawdt_acpi_ca;
extern struct cfattach plcom_acpi_ca;
extern struct cfattach acpipchb_ca;
extern struct cfattach mesongxbb_clkc_ca;
extern struct cfattach mesongxbb_aoclkc_ca;
extern struct cfattach mesong12_clkc_ca;
extern struct cfattach mesong12_aoclkc_ca;
extern struct cfattach meson_resets_ca;
extern struct cfattach meson_uart_ca;
extern struct cfattach meson_pinctrl_ca;
extern struct cfattach mesongx_mmc_ca;
extern struct cfattach meson_usbphy_ca;
extern struct cfattach mesongxl_usb2phy_ca;
extern struct cfattach mesongxl_usb3phy_ca;
extern struct cfattach mesong12_usb2phy_ca;
extern struct cfattach mesong12_usb3pciephy_ca;
extern struct cfattach meson_usbctrl_ca;
extern struct cfattach meson_rng_ca;
extern struct cfattach meson_dwmac_ca;
extern struct cfattach gxlphy_ca;
extern struct cfattach mesongx_wdt_ca;
extern struct cfattach meson_pwm_ca;
extern struct cfattach meson_thermal_ca;
extern struct cfattach apple_dart_ca;
extern struct cfattach apple_iic_ca;
extern struct cfattach apple_intc_ca;
extern struct cfattach apple_mbox_ca;
extern struct cfattach apple_nvme_ca;
extern struct cfattach apple_pcie_ca;
extern struct cfattach apple_pinctrl_ca;
extern struct cfattach apple_pmgr_ca;
extern struct cfattach apple_rtkitsmc_ca;
extern struct cfattach apple_wdog_ca;
extern struct cfattach bcmicu_ca;
extern struct cfattach bcmmbox_fdt_ca;
extern struct cfattach bcmmbox_acpi_ca;
extern struct cfattach bcmpmwdog_fdt_ca;
extern struct cfattach bcmrng_fdt_ca;
extern struct cfattach bcmaux_fdt_ca;
extern struct cfattach bcmcom_ca;
extern struct cfattach bcmcom_acpi_ca;
extern struct cfattach bcmemmc_ca;
extern struct cfattach bcmemmc_acpi_ca;
extern struct cfattach bcmemmc2_acpi_ca;
extern struct cfattach bcmsdhost_ca;
extern struct cfattach bcmdmac_fdt_ca;
extern struct cfattach bcmdwctwo_ca;
extern struct cfattach bcmspi_ca;
extern struct cfattach bsciic_fdt_ca;
extern struct cfattach bsciic_acpi_ca;
extern struct cfattach bcmgenfb_ca;
extern struct cfattach vchiq_fdt_ca;
extern struct cfattach vchiq_acpi_ca;
extern struct cfattach vcaudio_ca;
extern struct cfattach bcmgpio_ca;
extern struct cfattach bcmcprman_fdt_ca;
extern struct cfattach vcmbox_ca;
extern struct cfattach tegra_lic_ca;
extern struct cfattach tegra_mc_ca;
extern struct cfattach tegra_pmc_ca;
extern struct cfattach tegra_fuse_ca;
extern struct cfattach tegra210_car_ca;
extern struct cfattach tegra_gpio_ca;
extern struct cfattach tegra_timer_ca;
extern struct cfattach tegra_pinmux_ca;
extern struct cfattach tegra_apbdma_ca;
extern struct cfattach tegra210_xusbpad_ca;
extern struct cfattach tegra210xphy_ca;
extern struct cfattach tegra_com_ca;
extern struct cfattach tegra_i2c_ca;
extern struct cfattach tegra_rtc_ca;
extern struct cfattach tegra_usbphy_ca;
extern struct cfattach tegra_ehci_ca;
extern struct cfattach tegra_xusb_ca;
extern struct cfattach tegra_sdhc_ca;
extern struct cfattach tegra_soctherm_ca;
extern struct cfattach tegra_pcie_ca;
extern struct cfattach tegra_ahcisata_ca;
extern struct cfattach tegra_hdaudio_ca;
extern struct cfattach tegra_cec_ca;
extern struct cfattach imx8mq_ccm_ca;
extern struct cfattach imx7gpc_ca;
extern struct cfattach imxiomux_ca;
extern struct cfattach imxgpio_ca;
extern struct cfattach imx_com_ca;
extern struct cfattach enet_fdt_ca;
extern struct cfattach imx_ahcisata_ca;
extern struct cfattach imx8mqusbphy_ca;
extern struct cfattach imx_sdhc_ca;
extern struct cfattach imxi2c_ca;
extern struct cfattach imx6_dwhdmi_ca;
extern struct cfattach rk3328_cru_ca;
extern struct cfattach rk3399_cru_ca;
extern struct cfattach rk3399_pmucru_ca;
extern struct cfattach rk3588_cru_ca;
extern struct cfattach rk3328_iomux_ca;
extern struct cfattach rk3399_iomux_ca;
extern struct cfattach rk3588_iomux_ca;
extern struct cfattach rk_gpio_ca;
extern struct cfattach rk_i2c_ca;
extern struct cfattach rk_spi_ca;
extern struct cfattach rk_usb_ca;
extern struct cfattach rk_usbphy_ca;
extern struct cfattach rk_gmac_ca;
extern struct cfattach rk_eqos_ca;
extern struct cfattach rkpciephy_ca;
extern struct cfattach rkpcie_ca;
extern struct cfattach rkemmcphy_ca;
extern struct cfattach rk_tsadc_ca;
extern struct cfattach rk_pwm_ca;
extern struct cfattach rk_drm_ca;
extern struct cfattach rk_fb_ca;
extern struct cfattach rk_vop_ca;
extern struct cfattach rk_dwhdmi_ca;
extern struct cfattach rk_anxdp_ca;
extern struct cfattach rk_i2s_ca;
extern struct cfattach rk_v1crypto_ca;
extern struct cfattach exynos_uart_ca;
extern struct cfattach exynos_ohci_ca;
extern struct cfattach exynos_ehci_ca;
extern struct cfattach exynos_dwcmmc_ca;
extern struct cfattach sunxi_h3_ccu_ca;
extern struct cfattach sunxi_h3_r_ccu_ca;
extern struct cfattach sunxi_a64_ccu_ca;
extern struct cfattach sunxi_a64_r_ccu_ca;
extern struct cfattach sunxi_h6_ccu_ca;
extern struct cfattach sunxi_h6_r_ccu_ca;
extern struct cfattach sunxi_resets_ca;
extern struct cfattach sunxi_gates_ca;
extern struct cfattach sunxi_gmacclk_ca;
extern struct cfattach sunxi_nmi_ca;
extern struct cfattach sunxi_gpio_ca;
extern struct cfattach sunxi_pwm_ca;
extern struct cfattach sunxi_mmc_ca;
extern struct cfattach sunxi_usbphy_ca;
extern struct cfattach sunxi_usb3phy_ca;
extern struct cfattach sunxi_twi_ca;
extern struct cfattach sunxi_rsb_ca;
extern struct cfattach sunxi_rtc_ca;
extern struct cfattach sunxi_emac_ca;
extern struct cfattach sunxi_gmac_ca;
extern struct cfattach sunxi_wdt_ca;
extern struct cfattach sun6i_dma_ca;
extern struct cfattach sunxi_codec_ca;
extern struct cfattach sun8i_codec_ca;
extern struct cfattach h3_codec_ca;
extern struct cfattach a64_acodec_ca;
extern struct cfattach sunxi_i2s_ca;
extern struct cfattach sunxi_musb_ca;
extern struct cfattach sunxi_sid_ca;
extern struct cfattach sunxi_thermal_ca;
extern struct cfattach sunxi_sata_ca;
extern struct cfattach sunxi_sramc_ca;
extern struct cfattach sun6i_spi_ca;
extern struct cfattach sunxi_de2bus_ca;
extern struct cfattach sunxi_de2ccu_ca;
extern struct cfattach sunxi_mixer_ca;
extern struct cfattach sunxi_lcdc_ca;
extern struct cfattach sunxi_drm_ca;
extern struct cfattach sunxi_fb_ca;
extern struct cfattach sunxi_dwhdmi_ca;
extern struct cfattach sunxi_hdmiphy_ca;
extern struct cfattach sun8i_crypto_ca;

/* locators */
static int loc[805] = {
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, 1, 1, 0x1050, 0x114, -1,
	-1, 1, 1, 0x1050, 0x115, -1, -1, 1,
	2, 0x1050, 0x116, -1, -1, 1, 1, 0x1050,
	0x405, -1, -1, 1, 1, 0x1050, 0x406, -1,
	-1, 1, 2, 0x1050, 0x407, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, 1, -1, 1, -1, 1,
	-1, 1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, 10, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, 10, 10, 10, 10,
	10, 4, 4, 4, 4, -1, 10, -1,
	10, 10, 10, 10, 10, 3, 0, 0,
	0, 10, 10, 10, 10, 10, 10, 10,
	10, 10, 10, 10, 10, 10, 10, 10,
	10, 10, 10, 10, 10, 10, 10, 10,
	10, 10, 10, 10, 10, 10, 10, 0,
	4, 4, 4, 1, 1, 10, 10, 10,
	10, 10, 5, 0, 5, 5, 1, 10,
	10, 10, 10, 10, 0, 0, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, 4, 1,
	2, 1, 10, 10, 1, 2, 2, 2,
	2, 2, 4, 2, 10, 9, 9, 9,
	9, 9, 10, 10, -1, 10, 3, 10,
	3, 10, 1, 2, 10, 10, 0, 10,
	1, 10, 10, 10, 1, 10, 10, 10,
	10, 10, 3, 1, 1, 4, 4, 4,
	3, 2, 10, 10, 4, 10, 4, 10,
	10, 10, 10, 10, 2, 2, 2, 3,
	4, 10, 9, 4, 2, 2, 2, 2,
	3, 3, 3, 4, 10, 9, 9, 10,
	10, 10, 3, 5, 10, 10, 10, 4,
	2, 2, 2, 2, 2, 2, 1, 1,
	2, 2, 3, 3, 10, 9, 9, 10,
	4, 4, 10, 10, 4, 10, 10, 10,
	10, 10, 4, 10, 1, 10, 4, 3,
	10, 10, 5, 9, 10,
};

static const struct cfparent pspec0 = {
	"fdt", NULL, 0
};
static const struct cfparent pspec1 = {
	"acpibus", "acpifdt", DVUNIT_ANY
};
static const struct cfparent pspec2 = {
	"acpinodebus", "acpi", DVUNIT_ANY
};
static const struct cfparent pspec3 = {
	"acpisdtbus", "acpi", DVUNIT_ANY
};
static const struct cfparent pspec4 = {
	"acpimadtbus", "acpi", DVUNIT_ANY
};
static const struct cfparent pspec5 = {
	"cpu", "cpu", DVUNIT_ANY
};
static const struct cfparent pspec6 = {
	"wskbddev", "gpiokeys", DVUNIT_ANY
};
static const struct cfparent pspec7 = {
	"mpcorebus", "gtmr", DVUNIT_ANY
};
static const struct cfparent pspec8 = {
	"acpigtdtbus", "acpi", DVUNIT_ANY
};
static const struct cfparent pspec9 = {
	"mpcorebus", "gic", DVUNIT_ANY
};
static const struct cfparent pspec10 = {
	"bcmmboxbus", "bcmmbox", DVUNIT_ANY
};
static const struct cfparent pspec11 = {
	"rkiomux", "rkiomux", DVUNIT_ANY
};
static const struct cfparent pspec12 = {
	"gpiobus", NULL, 0
};
static const struct cfparent pspec13 = {
	"tegra210xpad", "tegra210xpad", DVUNIT_ANY
};
static const struct cfparent pspec14 = {
	"pcibus", NULL, 0
};
static const struct cfparent pspec15 = {
	"pci", "pci", DVUNIT_ANY
};
static const struct cfparent pspec16 = {
	"pcibus", "ppb", DVUNIT_ANY
};
static const struct cfparent pspec17 = {
	"mskc", "mskc", DVUNIT_ANY
};
static const struct cfparent pspec18 = {
	"mii", NULL, 0
};
static const struct cfparent pspec19 = {
	"puc", "puc", DVUNIT_ANY
};
static const struct cfparent pspec20 = {
	"i2cbus", NULL, 0
};
static const struct cfparent pspec21 = {
	"iic", "iic", DVUNIT_ANY
};
static const struct cfparent pspec22 = {
	"as3722pmic", "as3722pmic", DVUNIT_ANY
};
static const struct cfparent pspec23 = {
	"axppmic", "axppmic", DVUNIT_ANY
};
static const struct cfparent pspec24 = {
	"rkpmic", "rkpmic", DVUNIT_ANY
};
static const struct cfparent pspec25 = {
	"sdmmcbus", NULL, 0
};
static const struct cfparent pspec26 = {
	"sdmmc", "sdmmc", 0
};
static const struct cfparent pspec27 = {
	"sdmmc", "sdmmc", 1
};
static const struct cfparent pspec28 = {
	"sdmmc", "sdmmc", 2
};
static const struct cfparent pspec29 = {
	"sdmmc", "sdmmc", 3
};
static const struct cfparent pspec30 = {
	"sdmmc", "sdmmc", DVUNIT_ANY
};
static const struct cfparent pspec31 = {
	"ata", NULL, 0
};
static const struct cfparent pspec32 = {
	"atapi", NULL, 0
};
static const struct cfparent pspec33 = {
	"ata_hl", "atabus", DVUNIT_ANY
};
static const struct cfparent pspec34 = {
	"atapibus", "atapibus", DVUNIT_ANY
};
static const struct cfparent pspec35 = {
	"nvme", "nvme", DVUNIT_ANY
};
static const struct cfparent pspec36 = {
	"spibus", NULL, 0
};
static const struct cfparent pspec37 = {
	"spi", "spi", DVUNIT_ANY
};
static const struct cfparent pspec38 = {
	"spiflashbus", NULL, 0
};
static const struct cfparent pspec39 = {
	"vchiqbus", "vchiq", DVUNIT_ANY
};
static const struct cfparent pspec40 = {
	"hdaudiobus", NULL, 0
};
static const struct cfparent pspec41 = {
	"audiobus", NULL, 0
};
static const struct cfparent pspec42 = {
	"audio", "audio", DVUNIT_ANY
};
static const struct cfparent pspec43 = {
	"hdmicecbus", NULL, 0
};
static const struct cfparent pspec44 = {
	"rkfbbus", "rkdrm", DVUNIT_ANY
};
static const struct cfparent pspec45 = {
	"sunxifbbus", "sunxidrm", DVUNIT_ANY
};
static const struct cfparent pspec46 = {
	"wsemuldisplaydev", NULL, 0
};
static const struct cfparent pspec47 = {
	"radeonfbbus", NULL, 0
};
static const struct cfparent pspec48 = {
	"rkusb", "rkusb", DVUNIT_ANY
};
static const struct cfparent pspec49 = {
	"usbus", NULL, 0
};
static const struct cfparent pspec50 = {
	"usbroothubif", "usb", DVUNIT_ANY
};
static const struct cfparent pspec51 = {
	"usbdevif", "uhub", DVUNIT_ANY
};
static const struct cfparent pspec52 = {
	"usbifif", "uhub", DVUNIT_ANY
};
static const struct cfparent pspec53 = {
	"uhidbus", "uhidev", DVUNIT_ANY
};
static const struct cfparent pspec54 = {
	"wsmousedev", "ums", DVUNIT_ANY
};
static const struct cfparent pspec55 = {
	"wsmousedev", "uts", DVUNIT_ANY
};
static const struct cfparent pspec56 = {
	"wskbddev", "ukbd", DVUNIT_ANY
};
static const struct cfparent pspec57 = {
	"wsmousedev", "uep", DVUNIT_ANY
};
static const struct cfparent pspec58 = {
	"wsemuldisplaydev", "udl", DVUNIT_ANY
};
static const struct cfparent pspec59 = {
	"ucombus", "umodem", DVUNIT_ANY
};
static const struct cfparent pspec60 = {
	"scsi", "umass", DVUNIT_ANY
};
static const struct cfparent pspec61 = {
	"scsibus", "scsibus", DVUNIT_ANY
};
static const struct cfparent pspec62 = {
	"atapi", "umass", DVUNIT_ANY
};
static const struct cfparent pspec63 = {
	"usbifif", NULL, 0
};
static const struct cfparent pspec64 = {
	"audiobus", "uaudio", DVUNIT_ANY
};
static const struct cfparent pspec65 = {
	"irbus", "uirda", DVUNIT_ANY
};
static const struct cfparent pspec66 = {
	"irbus", "stuirda", DVUNIT_ANY
};
static const struct cfparent pspec67 = {
	"irbus", "ustir", DVUNIT_ANY
};
static const struct cfparent pspec68 = {
	"irbus", "udsir", DVUNIT_ANY
};
static const struct cfparent pspec69 = {
	"irbus", "irmce", DVUNIT_ANY
};
static const struct cfparent pspec70 = {
	"ucombus", "uark", DVUNIT_ANY
};
static const struct cfparent pspec71 = {
	"ucombus", "ubsa", DVUNIT_ANY
};
static const struct cfparent pspec72 = {
	"ucombus", "uchcom", DVUNIT_ANY
};
static const struct cfparent pspec73 = {
	"ucombus", "uftdi", DVUNIT_ANY
};
static const struct cfparent pspec74 = {
	"ucombus", "uipaq", DVUNIT_ANY
};
static const struct cfparent pspec75 = {
	"ucombus", "umct", DVUNIT_ANY
};
static const struct cfparent pspec76 = {
	"ucombus", "uplcom", DVUNIT_ANY
};
static const struct cfparent pspec77 = {
	"ucombus", "uslsa", DVUNIT_ANY
};
static const struct cfparent pspec78 = {
	"ucombus", "uvscom", DVUNIT_ANY
};
static const struct cfparent pspec79 = {
	"ucombus", "umcs", DVUNIT_ANY
};
static const struct cfparent pspec80 = {
	"ucombus", "uxrcom", DVUNIT_ANY
};
static const struct cfparent pspec81 = {
	"ucombus", "uvisor", DVUNIT_ANY
};
static const struct cfparent pspec82 = {
	"ucombus", "ukyopon", DVUNIT_ANY
};
static const struct cfparent pspec83 = {
	"scsi", "usscanner", DVUNIT_ANY
};
static const struct cfparent pspec84 = {
	"radiodev", "udsbr", DVUNIT_ANY
};
static const struct cfparent pspec85 = {
	"radiodev", "slurm", DVUNIT_ANY
};
static const struct cfparent pspec86 = {
	"ucombus", "u3g", DVUNIT_ANY
};
static const struct cfparent pspec87 = {
	"ucombus", "ugensa", DVUNIT_ANY
};
static const struct cfparent pspec88 = {
	"irbus", "emdtv", DVUNIT_ANY
};
static const struct cfparent pspec89 = {
	"videobus", NULL, 0
};
static const struct cfparent pspec90 = {
	"dtvbus", NULL, 0
};
static const struct cfparent pspec91 = {
	"btbus", "ubt", DVUNIT_ANY
};
static const struct cfparent pspec92 = {
	"midibus", NULL, 0
};
static const struct cfparent pspec93 = {
	"virtio", "virtio", DVUNIT_ANY
};
static const struct cfparent pspec94 = {
	"scsi", NULL, 0
};

#define NORM FSTATE_NOTFOUND
#define STAR FSTATE_STAR

struct cfdata cfdata[] = {
    /* driver           attachment    unit state      loc   flags  pspec */
/*125: xhci* at fdt? pass 10 */
    { "xhci",		"dwc3_fdt",	 0, STAR, loc+601,      0, &pspec0 },
// /*208: scsibus* at umass? channel -1 */
    { "scsibus",	"scsibus",	 0, STAR, loc+649,      0, &pspec60 },
/*209: scsibus* at usscanner? channel -1 */
    { "scsibus",	"scsibus",	 0, STAR, loc+650,      0, &pspec83 },
/*210: scsibus* at scsi? channel -1 */
    { "scsibus",	"scsibus",	 0, STAR, loc+651,      0, &pspec94 },
/*215: sd* at scsibus? target -1 lun -1 */
    { "sd",		"sd",		 0, STAR, loc+518,      0, &pspec61 },
/*222: usb* at usbus? */
    { "usb",		"usb",		 0, STAR,    NULL,      0, &pspec49 },
/*223: uhub* at usb? */
    { "uhub",		"uroothub",	 0, STAR,    NULL,      0, &pspec50 },
/*224: uhub* at uhub? port -1 configuration -1 interface -1 vendor -1 product -1 release -1 */
    { "uhub",		"uhub",		 0, STAR, loc+ 12,      0, &pspec51 },
/*251: uhidev* at uhub? port -1 configuration -1 interface -1 vendor -1 product -1 release -1 */
    { "uhidev",		"uhidev",	 0, STAR, loc+ 78,      0, &pspec52 },
/*252: uhid* at uhidev? reportid -1 */
    { "uhid",		"uhid",		 0, STAR, loc+672,      0, &pspec53 },
/*253: ukbd* at uhidev? reportid -1 */
    { "ukbd",		"ukbd",		 0, STAR, loc+673,      0, &pspec53 },
/*254: ums* at uhidev? reportid -1 */
    { "ums",		"ums",		 0, STAR, loc+674,      0, &pspec53 },
/*255: uts* at uhidev? reportid -1 */
    { "uts",		"uts",		 0, STAR, loc+675,      0, &pspec53 },
/*259: umass* at uhub? port -1 configuration -1 interface -1 vendor -1 product -1 release -1 */
    { "umass",		"umass",	 0, STAR, loc+ 96,      0, &pspec52 },
    { NULL,		NULL,		 0,    0,    NULL,      0, NULL }
};

static struct cfattach * const xhci_cfattachinit[] = {
	&dwc3_fdt_ca, NULL
};
static struct cfattach * const scsibus_cfattachinit[] = {
	&scsibus_ca, NULL
};
static struct cfattach * const sd_cfattachinit[] = {
	&sd_ca, NULL
};
static struct cfattach * const usb_cfattachinit[] = {
	&usb_ca, NULL
};
static struct cfattach * const uhub_cfattachinit[] = {
	&uroothub_ca, &uhub_ca, NULL
};
static struct cfattach * const uhidev_cfattachinit[] = {
	&uhidev_ca, NULL
};
static struct cfattach * const uhid_cfattachinit[] = {
	&uhid_ca, NULL
};
static struct cfattach * const ukbd_cfattachinit[] = {
	&ukbd_ca, NULL
};
static struct cfattach * const ums_cfattachinit[] = {
	&ums_ca, NULL
};
static struct cfattach * const uts_cfattachinit[] = {
	&uts_ca, NULL
}; 
static struct cfattach * const umass_cfattachinit[] = { 
 	&umass_ca, NULL
};


const struct cfattachinit cfattachinit[] = {
	{ "xhci", xhci_cfattachinit },
//	{ "simplebus", simplebus_cfattachinit },
	{ "scsibus", scsibus_cfattachinit },
	{ "sd", sd_cfattachinit },
	{ "usb", usb_cfattachinit },
	{ "uhub", uhub_cfattachinit },
	{ "uhidev", uhidev_cfattachinit },
	{ "uhid", uhid_cfattachinit },
	{ "ukbd", ukbd_cfattachinit },
	{ "ums", ums_cfattachinit },
	{ "uts", uts_cfattachinit },
	{ "umass", umass_cfattachinit },
	{ NULL, NULL }
};

const short cfroots[] = {
	327 /* armfdt0 */,
	-1
};

// /* pseudo-devices */

// const struct pdevinit pdevinit[] = {
// 	{ cpuctlattach, 1 },
// 	{ rndattach, 1 },
// 	{ putterattach, 1 },
// 	{ cryptoattach, 1 },
// 	{ swcryptoattach, 1 },
// 	{ vndattach, 1 },
// 	{ drvctlattach, 1 },
// 	{ cgdattach, 1 },
// 	{ bpfilterattach, 1 },
// 	{ carpattach, 1 },
// 	{ loopattach, 1 },
// 	{ bridgeattach, 1 },
// 	{ vlanattach, 1 },
// 	{ pppattach, 1 },
// 	{ pppoeattach, 1 },
// 	{ tunattach, 1 },
// 	{ tapattach, 1 },
// 	{ gifattach, 1 },
// 	{ ipsecifattach, 1 },
// 	{ greattach, 1 },
// 	{ npfattach, 1 },
// 	{ ptyattach, 1 },
// 	{ clockctlattach, 1 },
// 	{ ksymsattach, 1 },
// 	{ lockstatattach, 1 },
// 	{ veriexecattach, 1 },
// 	{ openfirmattach, 1 },
// 	{ tprofattach, 1 },
// 	{ wsmuxattach, 1 },
// 	{ wsfontattach, 1 },
// 	{ sequencerattach, 1 },
// 	{ 0, 0 }
// };