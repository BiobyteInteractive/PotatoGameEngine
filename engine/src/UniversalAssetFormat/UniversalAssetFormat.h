#pragma once
#ifndef UNIVERSAL_ASSET_FORMAT_H
#define UNIVERSAL_ASSET_FORMAT_H

#define DllExport __declspec( dllexport )

class DllExport UniversalAsset {
    public:
        UniversalAsset();
        ~UniversalAsset();

        void LoadAsset();
    public:
};

#endif