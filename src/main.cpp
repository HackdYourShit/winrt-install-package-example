#include <iostream>
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.Store.Preview.InstallControl.h>
#include <winrt/Windows.Management.Deployment.h>
#include <windows.h>

// The windowsapps library that comes with the Windows SDK contains C++/WinRT symbols
#pragma comment(lib, "windowsapp")

#define MESSENGER_PRODUCT_ID "9wzdncrf0083"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Store::Preview::InstallControl;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Management::Deployment;

int main() {
	winrt::init_apartment(); // initializes the Windows Runtime on the current thread (required)
	std::cout << "Installing app..." << std::endl;

	// We use the AppInstallManager class to install the app from the Microsoft Store
	AppInstallManager installManager;
	AppInstallItem item = installManager.StartAppInstallAsync(winrt::to_hstring(MESSENGER_PRODUCT_ID), L"", false, true).get();
	item.LaunchAfterInstall(false);
	item.CompletedInstallToastNotificationMode(AppInstallationToastNotificationMode::NoToast);

	HANDLE completedEvent = CreateEvent(NULL, true, false, "CompletedEvent");
	item.StatusChanged([completedEvent](const AppInstallItem& sender, const IInspectable& item) {
		AppInstallStatus status = sender.GetCurrentStatus();
		if (status.InstallState() == AppInstallState::Completed) {
			SetEvent(completedEvent);
		}
	});

	WaitForSingleObject(completedEvent, INFINITE);
	std::cout << "\nThe application has been installed!\nTime to uninstall it..." << std::endl;
	
	// Now we uninstall the app we just installed. To do this, we need to find the full name of the package, which
	// is not given to use from the AppInstallManager. We have to hope that there is a single package with the
	// installed app's family name.
	// IMPORTANT: you must be an administrator to use FindPackages()
	PackageManager packageManager;
	winrt::hstring packageFullName;
	int numPackages = 0;
	for (const Package& package : packageManager.FindPackages(item.PackageFamilyName())) {
		numPackages++;
		packageFullName = package.Id().FullName();
	}
	if (numPackages != 1) {
		std::cout << "Failed to find package!" << std::endl;
		return 1;
	}

	auto operation = packageManager.RemovePackageAsync(packageFullName);
	operation.get();
	switch (operation.Status()) {
		case AsyncStatus::Completed:
			std::cout << "Uninstallation complete!" << std::endl;
			break;
		case AsyncStatus::Error:
			std::cout << "Uninstallation errored: " << winrt::to_string(operation.GetResults().ErrorText()) << std::endl;
			break;
		default:
			std::cout << "Unknown state" << std::endl;
	}

    return 0;
}
