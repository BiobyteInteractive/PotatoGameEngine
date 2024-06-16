#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>

#include <imgui.h>
#include <toml.hpp>

#include "Theme.h"
#include "toml/get.hpp"
#include "toml/parser.hpp"

ImVec4 ConvertRGBAStringToImVec4(const std::string& rgbaString) {
    std::vector<float> values;
    std::stringstream ss(rgbaString);
    std::string item;

    std::getline(ss, item, '(');

    while (std::getline(ss, item, ',')) {
        try {
            if (!item.empty() && item.back() == ')') {
                item.pop_back();
            }

            float value = std::stof(item);
            if (value > 1.0f) {
                value /= 255.0f;
            }
            values.push_back(value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << '\n';
            return ImVec4(0, 0, 0, -1);
        }
    }

    if (values.size() != 4) {
        std::cerr << "Invalid RGBA string format.\n";
        return ImVec4(0, 0, 0, -1);
    }

    return ImVec4(values[0], values[1], values[2], values[3]);
}

ImVec2 FloatVectorToImVec2(std::vector<float> vector) {
    return ImVec2(vector[0], vector[1]);
}

ImGuiDir StringToImGuiDir(std::string directionString) {
    if (directionString == "Right")
        return ImGuiDir_Right;

    return ImGuiDir_Left;
}

Theme::Theme(std::string themePath) {
    auto theme = toml::parse(themePath);

    this->m_Alpha                     = toml::find<float>(theme, "alpha");
    this->m_DisabledAlpha             = toml::find<float>(theme, "disabledAlpha");
    this->m_WindowPadding             = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "windowPadding"));
    this->m_WindowRounding            = toml::find<float>(theme, "windowRounding");
    this->m_WindowBorderSize          = toml::find<float>(theme, "windowBorderSize");
    this->m_WindowMinSize             = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "windowMinSize"));
    this->m_WindowTitleAlign          = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "windowTitleAlign"));
    this->m_WindowMenuButtonPosition  = StringToImGuiDir(toml::find<std::string>(theme, "windowMenuButtonPosition"));
    this->m_ChildRounding             = toml::find<float>(theme, "childRounding");
    this->m_ChildBorderSize           = toml::find<float>(theme, "childBorderSize");
    this->m_PopupRounding             = toml::find<float>(theme, "popupRounding");
    this->m_PopupBorderSize           = toml::find<float>(theme, "popupBorderSize");
    this->m_FramePadding              = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "framePadding"));
    this->m_FrameRounding             = toml::find<float>(theme, "frameRounding");
    this->m_FrameBorderSize           = toml::find<float>(theme, "frameBorderSize");
    this->m_ItemSpacing               = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "itemSpacing"));
    this->m_ItemInnerSpacing          = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "itemInnerSpacing"));
    this->m_CellPadding               = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "cellPadding"));
    this->m_IndentSpacing             = toml::find<float>(theme, "indentSpacing");
    this->m_ColumnsMinSpacing         = toml::find<float>(theme, "columnsMinSpacing");
    this->m_ScrollbarSize             = toml::find<float>(theme, "scrollbarSize");
    this->m_ScrollbarRounding         = toml::find<float>(theme, "scrollbarRounding");
    this->m_GrabMinSize               = toml::find<float>(theme, "grabMinSize");
    this->m_GrabRounding              = toml::find<float>(theme, "grabRounding");
    this->m_TabRounding               = toml::find<float>(theme, "tabRounding");
    this->m_TabBorderSize             = toml::find<float>(theme, "tabBorderSize");
    this->m_TabMinWidthForCloseButton = toml::find<float>(theme, "tabMinWidthForCloseButton");
    this->m_ColorButtonPosition       = StringToImGuiDir(toml::find<std::string>(theme, "colorButtonPosition"));
    this->m_ButtonTextAlign           = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "buttonTextAlign"));
    this->m_SelectableTextAlign       = FloatVectorToImVec2(toml::find<std::vector<float>>(theme, "selectableTextAlign"));

    std::map<std::string, std::string> colors = toml::find<std::map<std::string, std::string>>(theme, "colors");

    this->m_Text                  = ConvertRGBAStringToImVec4(colors["Text"]);
    this->m_TextDisabled          = ConvertRGBAStringToImVec4(colors["TextDisabled"]);
    this->m_WindowBg              = ConvertRGBAStringToImVec4(colors["WindowBg"]);
    this->m_ChildBg               = ConvertRGBAStringToImVec4(colors["ChildBg"]);
    this->m_PopupBg               = ConvertRGBAStringToImVec4(colors["PopupBg"]);
    this->m_Border                = ConvertRGBAStringToImVec4(colors["Border"]);
    this->m_BorderShadow          = ConvertRGBAStringToImVec4(colors["BorderShadow"]);
    this->m_FrameBg               = ConvertRGBAStringToImVec4(colors["FrameBg"]);
    this->m_FrameBgHovered        = ConvertRGBAStringToImVec4(colors["FrameBgHovered"]);
    this->m_FrameBgActive         = ConvertRGBAStringToImVec4(colors["FrameBgActive"]);
    this->m_TitleBg               = ConvertRGBAStringToImVec4(colors["TitleBg"]);
    this->m_TitleBgActive         = ConvertRGBAStringToImVec4(colors["TitleBgActive"]);
    this->m_TitleBgCollapsed      = ConvertRGBAStringToImVec4(colors["TitleBgCollapsed"]);
    this->m_MenuBarBg             = ConvertRGBAStringToImVec4(colors["MenuBarBg"]);
    this->m_ScrollbarBg           = ConvertRGBAStringToImVec4(colors["ScrollbarBg"]);
    this->m_ScrollbarGrab         = ConvertRGBAStringToImVec4(colors["ScrollbarGrab"]);
    this->m_ScrollbarGrabHovered  = ConvertRGBAStringToImVec4(colors["ScrollbarGrabHovered"]);
    this->m_ScrollbarGrabActive   = ConvertRGBAStringToImVec4(colors["ScrollbarGrabActive"]);
    this->m_CheckMark             = ConvertRGBAStringToImVec4(colors["CheckMark"]);
    this->m_SliderGrab            = ConvertRGBAStringToImVec4(colors["SliderGrab"]);
    this->m_SliderGrabActive      = ConvertRGBAStringToImVec4(colors["SliderGrabActive"]);
    this->m_Button                = ConvertRGBAStringToImVec4(colors["Button"]);
    this->m_ButtonHovered         = ConvertRGBAStringToImVec4(colors["ButtonHovered"]);
    this->m_ButtonActive          = ConvertRGBAStringToImVec4(colors["ButtonActive"]);
    this->m_Header                = ConvertRGBAStringToImVec4(colors["Header"]);
    this->m_HeaderHovered         = ConvertRGBAStringToImVec4(colors["HeaderHovered"]);
    this->m_HeaderActive          = ConvertRGBAStringToImVec4(colors["HeaderActive"]);
    this->m_Separator             = ConvertRGBAStringToImVec4(colors["Separator"]);
    this->m_SeparatorHovered      = ConvertRGBAStringToImVec4(colors["SeparatorHovered"]);
    this->m_SeparatorActive       = ConvertRGBAStringToImVec4(colors["SeparatorActive"]);
    this->m_ResizeGrip            = ConvertRGBAStringToImVec4(colors["ResizeGrip"]);
    this->m_ResizeGripHovered     = ConvertRGBAStringToImVec4(colors["ResizeGripHovered"]);
    this->m_ResizeGripActive      = ConvertRGBAStringToImVec4(colors["ResizeGripActive"]);
    this->m_Tab                   = ConvertRGBAStringToImVec4(colors["Tab"]);
    this->m_TabHovered            = ConvertRGBAStringToImVec4(colors["TabHovered"]);
    this->m_TabActive             = ConvertRGBAStringToImVec4(colors["TabActive"]);
    this->m_TabUnfocused          = ConvertRGBAStringToImVec4(colors["TabUnfocused"]);
    this->m_TabUnfocusedActive    = ConvertRGBAStringToImVec4(colors["TabUnfocusedActive"]);
    this->m_PlotLines             = ConvertRGBAStringToImVec4(colors["PlotLines"]);
    this->m_PlotLinesHovered      = ConvertRGBAStringToImVec4(colors["PlotLinesHovered"]);
    this->m_PlotHistogram         = ConvertRGBAStringToImVec4(colors["PlotHistogram"]);
    this->m_PlotHistogramHovered  = ConvertRGBAStringToImVec4(colors["PlotHistogramHovered"]);
    this->m_TableHeaderBg         = ConvertRGBAStringToImVec4(colors["TableHeaderBg"]);
    this->m_TableBorderStrong     = ConvertRGBAStringToImVec4(colors["TableBorderStrong"]);
    this->m_TableBorderLight      = ConvertRGBAStringToImVec4(colors["TableBorderLight"]);
    this->m_TableRowBg            = ConvertRGBAStringToImVec4(colors["TableRowBg"]);
    this->m_TableRowBgAlt         = ConvertRGBAStringToImVec4(colors["TableRowBgAlt"]);
    this->m_TextSelectedBg        = ConvertRGBAStringToImVec4(colors["TextSelectedBg"]);
    this->m_DragDropTarget        = ConvertRGBAStringToImVec4(colors["DragDropTarget"]);
    this->m_NavHighlight          = ConvertRGBAStringToImVec4(colors["NavHighlight"]);
    this->m_NavWindowingHighlight = ConvertRGBAStringToImVec4(colors["NavWindowingHighlight"]);
    this->m_NavWindowingDimBg     = ConvertRGBAStringToImVec4(colors["NavWindowingDimBg"]);
    this->m_ModalWindowDimBg      = ConvertRGBAStringToImVec4(colors["ModalWindowDimBg"]);
}

void Theme::SetTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha                     = this->m_Alpha;
	style.DisabledAlpha             = this->m_DisabledAlpha;
	style.WindowPadding             = this->m_WindowPadding;
	style.WindowRounding            = this->m_WindowRounding;
	style.WindowBorderSize          = this->m_WindowBorderSize;
	style.WindowMinSize             = this->m_WindowMinSize;
	style.WindowTitleAlign          = this->m_WindowTitleAlign;
	style.WindowMenuButtonPosition  = this->m_WindowMenuButtonPosition;
	style.ChildRounding             = this->m_ChildRounding;
	style.ChildBorderSize           = this->m_ChildBorderSize;
	style.PopupRounding             = this->m_PopupRounding;
	style.PopupBorderSize           = this->m_PopupBorderSize;
	style.FramePadding              = this->m_FramePadding;
	style.FrameRounding             = this->m_FrameRounding;
	style.FrameBorderSize           = this->m_FrameBorderSize;
	style.ItemSpacing               = this->m_ItemSpacing;
	style.ItemInnerSpacing          = this->m_ItemInnerSpacing;
	style.CellPadding               = this->m_CellPadding;
	style.IndentSpacing             = this->m_IndentSpacing;
	style.ColumnsMinSpacing         = this->m_ColumnsMinSpacing;
	style.ScrollbarSize             = this->m_ScrollbarSize;
	style.ScrollbarRounding         = this->m_ScrollbarRounding;
	style.GrabMinSize               = this->m_GrabMinSize;
	style.GrabRounding              = this->m_GrabRounding;
	style.TabRounding               = this->m_TabRounding;
	style.TabBorderSize             = this->m_TabBorderSize;
	style.TabMinWidthForCloseButton = this->m_TabMinWidthForCloseButton;
	style.ColorButtonPosition       = this->m_ColorButtonPosition;
	style.ButtonTextAlign           = this->m_ButtonTextAlign;
	style.SelectableTextAlign       = this->m_SelectableTextAlign;
	
	style.Colors[ImGuiCol_Text]                  = this->m_Text;
	style.Colors[ImGuiCol_TextDisabled]          = this->m_TextDisabled;
	style.Colors[ImGuiCol_WindowBg]              = this->m_WindowBg;
	style.Colors[ImGuiCol_ChildBg]               = this->m_ChildBg;
	style.Colors[ImGuiCol_PopupBg]               = this->m_PopupBg;
	style.Colors[ImGuiCol_Border]                = this->m_Border;
	style.Colors[ImGuiCol_BorderShadow]          = this->m_BorderShadow;
	style.Colors[ImGuiCol_FrameBg]               = this->m_FrameBg;
	style.Colors[ImGuiCol_FrameBgHovered]        = this->m_FrameBgHovered;
	style.Colors[ImGuiCol_FrameBgActive]         = this->m_FrameBgActive;
	style.Colors[ImGuiCol_TitleBg]               = this->m_TitleBg;
	style.Colors[ImGuiCol_TitleBgActive]         = this->m_TitleBgActive;
	style.Colors[ImGuiCol_TitleBgCollapsed]      = this->m_TitleBgCollapsed;
	style.Colors[ImGuiCol_MenuBarBg]             = this->m_MenuBarBg;
	style.Colors[ImGuiCol_ScrollbarBg]           = this->m_ScrollbarBg;
	style.Colors[ImGuiCol_ScrollbarGrab]         = this->m_ScrollbarGrab;
	style.Colors[ImGuiCol_ScrollbarGrabHovered]  = this->m_ScrollbarGrabHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive]   = this->m_ScrollbarGrabActive;
	style.Colors[ImGuiCol_CheckMark]             = this->m_CheckMark;
	style.Colors[ImGuiCol_SliderGrab]            = this->m_SliderGrab;
	style.Colors[ImGuiCol_SliderGrabActive]      = this->m_SliderGrabActive;
	style.Colors[ImGuiCol_Button]                = this->m_Button;
	style.Colors[ImGuiCol_ButtonHovered]         = this->m_ButtonHovered;
	style.Colors[ImGuiCol_ButtonActive]          = this->m_ButtonActive;
	style.Colors[ImGuiCol_Header]                = this->m_Header;
	style.Colors[ImGuiCol_HeaderHovered]         = this->m_HeaderHovered;
	style.Colors[ImGuiCol_HeaderActive]          = this->m_HeaderActive;
	style.Colors[ImGuiCol_Separator]             = this->m_Separator;
	style.Colors[ImGuiCol_SeparatorHovered]      = this->m_SeparatorHovered;
	style.Colors[ImGuiCol_SeparatorActive]       = this->m_SeparatorActive;
	style.Colors[ImGuiCol_ResizeGrip]            = this->m_ResizeGrip;
	style.Colors[ImGuiCol_ResizeGripHovered]     = this->m_ResizeGripHovered;
	style.Colors[ImGuiCol_ResizeGripActive]      = this->m_ResizeGripActive;
	style.Colors[ImGuiCol_Tab]                   = this->m_Tab;
	style.Colors[ImGuiCol_TabHovered]            = this->m_TabHovered;
	style.Colors[ImGuiCol_TabActive]             = this->m_TabActive;
	style.Colors[ImGuiCol_TabUnfocused]          = this->m_TabUnfocused;
	style.Colors[ImGuiCol_TabUnfocusedActive]    = this->m_TabUnfocusedActive;
	style.Colors[ImGuiCol_PlotLines]             = this->m_PlotLines;
	style.Colors[ImGuiCol_PlotLinesHovered]      = this->m_PlotLinesHovered;
	style.Colors[ImGuiCol_PlotHistogram]         = this->m_PlotHistogram;
	style.Colors[ImGuiCol_PlotHistogramHovered]  = this->m_PlotHistogramHovered;
	style.Colors[ImGuiCol_TableHeaderBg]         = this->m_TableHeaderBg;
	style.Colors[ImGuiCol_TableBorderStrong]     = this->m_TableBorderStrong;
	style.Colors[ImGuiCol_TableBorderLight]      = this->m_TableBorderLight;
	style.Colors[ImGuiCol_TableRowBg]            = this->m_TableRowBg;
	style.Colors[ImGuiCol_TableRowBgAlt]         = this->m_TableRowBgAlt;
	style.Colors[ImGuiCol_TextSelectedBg]        = this->m_TextSelectedBg;
	style.Colors[ImGuiCol_DragDropTarget]        = this->m_DragDropTarget;
	style.Colors[ImGuiCol_NavHighlight]          = this->m_NavHighlight;
	style.Colors[ImGuiCol_NavWindowingHighlight] = this->m_NavWindowingHighlight ;
	style.Colors[ImGuiCol_NavWindowingDimBg]     = this->m_NavWindowingDimBg;
	style.Colors[ImGuiCol_ModalWindowDimBg]      = this->m_ModalWindowDimBg;
    style.Colors[ImGuiCol_DockingPreview]        = this->m_TabActive;
    style.Colors[ImGuiCol_DockingEmptyBg]        = this->m_WindowBg;
}

void Theme::SaveTheme() {

}