// MyUsbLowerFilterDevice.h
//
// Generated by DriverWizard 3.2.0 (Build 2485)
// Requires DDK and DriverWorks
// File created on 8/28/2008
//
// This include file contains the definition of a subclass of KWdmFilterDevice.
// WDM filter drivers declare a subclass of KWdmFilterDevice and override member
// functions to filter requests (IRPs) from the system.  The default behavior
// of base class methods is to pass all IRPs thru to the lower driver.  Only
// override those IRP handlers to add custom processing for a particular IRP.
//
#ifndef __MYUSBLOWERFILTERDEVICE_H__
#define __MYUSBLOWERFILTERDEVICE_H__

class MyUsbLowerFilterDevice : public KWdmFilterDevice
{
public:
	SAFE_DESTRUCTORS;
	MyUsbLowerFilterDevice(PDEVICE_OBJECT Pdo, ULONG Unit);
	~MyUsbLowerFilterDevice();

	// IRP handlers
	virtual NTSTATUS Read(KIrp I);
	virtual NTSTATUS Write(KIrp I);
	virtual NTSTATUS InternalDeviceControl(KIrp I);	
	virtual NTSTATUS OnStartDevice(KIrp I);
	virtual NTSTATUS OnRemoveDevice(KIrp I);
	virtual NTSTATUS OnQueryRemoveDevice(KIrp I);
	virtual NTSTATUS OnStopDevice(KIrp I);
	virtual NTSTATUS OnSurpriseRemoval(KIrp I);
	virtual NTSTATUS OnCancelRemoveDevice(KIrp I);
	virtual NTSTATUS OnQueryStopDevice(KIrp I);
	virtual NTSTATUS OnCancelStopDevice(KIrp I);

	MEMBER_PASSTHROUGH_COMPLETE(MyUsbLowerFilterDevice, IrpCompletionRoutine);

protected:
	// Member data
	KPnpLowerDevice	m_Lower;
	ULONG			m_Unit;

#ifdef __COMMENT_ONLY
		// The following member functions are actually defined by 
		// a DEVMEMBER_XXX or MEMBER_XXX macro (such as DEVMEMBER_DISPATCHERS).
		// The macro __COMMENT_ONLY never gets defined.  These comment-only
		// definitions simply allow easy navigation to the functions within
		// the Visual Studio IDE using the class browser.
	NTSTATUS IrpCompletionRoutine(KIrp I);	// __COMMENT_ONLY
#endif
};

#endif // __MYUSBLOWERFILTERDEVICE_H__