#include "FileUtils.h"

#include <Windows.h>
#include <winbase.h>
#include <shobjidl.h> 

std::string OpenFileDialog() {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | 
    COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, 
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        if (pszFilePath == nullptr) {
                            return "";
                        }

                        // Get the length of the resulting string
                        int size_needed = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, nullptr, 0, nullptr, nullptr);

                        // Allocate a string with the needed size
                        std::string strTo(size_needed, 0);

                        // Perform the conversion
                        WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, &strTo[0], size_needed, nullptr, nullptr);

                        // Remove the null terminator that WideCharToMultiByte adds
                        strTo.resize(size_needed - 1);

                        return strTo;
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return "";
}