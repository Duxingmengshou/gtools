#include <imgui.h>
#include <pugixml.hpp>

#include <cstdio>
#include <sstream>

#include "plugin_api.h"

namespace {

void RenderXmlFormatter() {
    static char input_buf[8192] = "<root><item>hello</item><value>42</value></root>";
    static char output_buf[8192] = "";
    static char status_buf[256] = "Ready.";

    ImGui::Begin("XML Formatter");
    ImGui::Text("Input XML and format it automatically.");

    if (ImGui::Button("Format")) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input_buf);
        if (result) {
            std::ostringstream oss;
            doc.save(oss, "  ", pugi::format_default, pugi::encoding_utf8);
            std::snprintf(output_buf, sizeof(output_buf), "%s", oss.str().c_str());
            std::snprintf(status_buf, sizeof(status_buf), "%s", "Format OK.");
        } else {
            std::snprintf(status_buf, sizeof(status_buf), "Parse error: %s", result.description());
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        input_buf[0] = '\0';
        output_buf[0] = '\0';
        std::snprintf(status_buf, sizeof(status_buf), "%s", "Cleared.");
    }

    ImGui::SameLine();
    ImGui::Text("Status: %s", status_buf);
    ImGui::Separator();

    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGuiTableFlags table_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp;
    if (ImGui::BeginTable("XmlPanels", 2, table_flags, ImVec2(0.0f, avail.y))) {
        ImGui::TableNextColumn();
        ImGui::BeginChild("InputPanel", ImVec2(0.0f, 0.0f), true);
        ImGui::TextUnformatted("Input");
        ImGui::Separator();
        ImGui::InputTextMultiline(
            "##Input",
            input_buf,
            sizeof(input_buf),
            ImVec2(-1.0f, -1.0f),
            ImGuiInputTextFlags_NoHorizontalScroll);
        ImGui::EndChild();

        ImGui::TableNextColumn();
        ImGui::BeginChild("OutputPanel", ImVec2(0.0f, 0.0f), true);
        ImGui::TextUnformatted("Output");
        ImGui::Separator();
        ImGui::InputTextMultiline(
            "##Output",
            output_buf,
            sizeof(output_buf),
            ImVec2(-1.0f, -1.0f),
            ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_NoHorizontalScroll);
        ImGui::EndChild();

        ImGui::EndTable();
    }
    ImGui::End();
}

PluginInfo g_plugin_info = {
    "XML Formatter",
    &RenderXmlFormatter
};

} // namespace

extern "C" PLUGIN_API PluginInfo* GetPluginInfo() {
    return &g_plugin_info;
}
