/***************************************************************
 * Name:      GrafyMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Maja Darczuk i Jan Walkiewicz ()
 * Created:   2024-12-19
 * Copyright: Maja Darczuk i Jan Walkiewicz ()
 * License:
 **************************************************************/
#include "GrafyMain.h"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>
#include <wx/frame.h>
#include <boost/locale.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/planar_canonical_ordering.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <wx/textdlg.h>

#undef _
#define _(s) wxString::FromUTF8(s)

//(*InternalHeaders(GrafyDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(GrafyDialog)
const long GrafyDialog::ID_STATICTEXT1 = wxNewId();
const long GrafyDialog::ID_BUTTON1 = wxNewId();
const long GrafyDialog::ID_TEXTCTRL1 = wxNewId();
const long GrafyDialog::ID_STATICTEXT2 = wxNewId();
const long GrafyDialog::ID_BUTTON2 = wxNewId();
const long GrafyDialog::ID_RADIOBOX1 = wxNewId();
const long GrafyDialog::ID_BUTTON3 = wxNewId();
const long GrafyDialog::ID_BUTTON4 = wxNewId();
const long GrafyDialog::ID_BUTTON5 = wxNewId();
const long GrafyDialog::ID_BUTTON6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GrafyDialog,wxDialog)
    //(*EventTable(GrafyDialog)
    //*)
END_EVENT_TABLE()

GrafyDialog::GrafyDialog(wxWindow* parent,wxWindowID id): backgroundImage("tlograf.jpg", wxBITMAP_TYPE_JPEG)
{
    //(*Initialize(GrafyDialog)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer9;

    Create(parent, wxID_ANY, _("graphApp"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxTRANSPARENT_WINDOW, _T("wxID_ANY"));
    SetClientSize(wxSize(690,430));
    FlexGridSizer1 = new wxFlexGridSizer(10, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Analiza grafu"), wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW, _T("ID_STATICTEXT1"));
    StaticText1->SetBackgroundColour(wxColour(252,252,252));
    wxFont StaticText1Font(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial Rounded MT Bold"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer2->Add(StaticText1, 1, wxALL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(1, 2, 0, 0);
    Button1 = new wxButton(this, ID_BUTTON1, _("Wczytaj plik:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    wxFont Button1Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button1->SetFont(Button1Font);
    FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("jeszcze nie wybrano..."), wxDefaultPosition, wxSize(305,30), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wxFont TextCtrl1Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_LIGHT,false,_T("Bahnschrift Light Condensed"),wxFONTENCODING_DEFAULT);
    TextCtrl1->SetFont(TextCtrl1Font);
    FlexGridSizer3->Add(TextCtrl1, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("UWAGA! Plik ma być w formacie (.graphml)"), wxDefaultPosition, wxDefaultSize, wxTRANSPARENT_WINDOW, _T("ID_STATICTEXT2"));
    StaticText2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    wxFont StaticText2Font(14,wxFONTFAMILY_ROMAN,wxFONTSTYLE_ITALIC,wxFONTWEIGHT_NORMAL,false,_T("Baskerville Old Face"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
    Button2 = new wxButton(this, ID_BUTTON2, _("Rysuj Graf"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    wxFont Button2Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button2->SetFont(Button2Font);
    FlexGridSizer5->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxString __wxRadioBoxChoices_1[3] =
    {
    	_("Na okręgu"),
    	_("Na okręgu losowo"),
    	_("Wewnątrz okręgu losowo")
    };
    RadioBox1 = new wxRadioBox(this, ID_RADIOBOX1, _("Wybierz layout:"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_ROWS, wxDefaultValidator, _T("ID_RADIOBOX1"));
    RadioBox1->SetBackgroundColour(wxColour(255,255,255));
    wxFont RadioBox1Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    RadioBox1->SetFont(RadioBox1Font);
    FlexGridSizer5->Add(RadioBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
    Button3 = new wxButton(this, ID_BUTTON3, _("Wyświetl wierzchołki"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    wxFont Button3Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button3->SetFont(Button3Font);
    FlexGridSizer6->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer6, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
    Button4 = new wxButton(this, ID_BUTTON4, _("Wyświetl krawędzie"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    wxFont Button4Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button4->SetFont(Button4Font);
    FlexGridSizer7->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer7, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
    Button5 = new wxButton(this, ID_BUTTON5, _("Typ grafu"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    wxFont Button5Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button5->SetFont(Button5Font);
    FlexGridSizer8->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer8, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    Button6 = new wxButton(this, ID_BUTTON6, _("Najkrótsza ścieżka"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    wxFont Button6Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    Button6->SetFont(Button6Font);
    FlexGridSizer9->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer9, 1, wxALL|wxEXPAND, 5);
    SetSizer(FlexGridSizer1);
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton2Click);
    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&GrafyDialog::OnRadioBox1Select);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton3Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton4Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton5Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GrafyDialog::OnButton6Click1);
    //*)

    SetIcon(wxICON(aaaa));
    Connect(wxEVT_PAINT, wxPaintEventHandler(GrafyDialog::OnPaint));
    srand(time(0));

}

GrafyDialog::~GrafyDialog()
{
    //(*Destroy(GrafyDialog)
    //*)
}

void GrafyDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void GrafyDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void GrafyDialog::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.DrawBitmap(backgroundImage, 0, 0, true);
}


// Definicja grafu
struct VertexProperties {
    std::string label;
    float x, y;

};

struct EdgeProperties {
    std::string label;
    int weight;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties> Graph;

// Globalny graf
Graph g;


// Klasa rysująca graf
class GraphWindow : public wxFrame {
public:
    GraphWindow(wxWindow* parent, const Graph& graph, int mode)
        : wxFrame(parent, wxID_ANY, "Rysowanie grafu", wxDefaultPosition, wxSize(800, 600)), graph(graph), drawMode(mode) {
        SetSizeHints(800, 600, 800, 600);
        Bind(wxEVT_PAINT, &GraphWindow::OnPaint, this);
        Bind(wxEVT_CLOSE_WINDOW, &GraphWindow::OnClose, this);
    }

private:
    const Graph& graph;
    int drawMode;

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        dc.SetBackground(wxBrush(wxColour(255, 255, 255)));
        dc.Clear();
        DrawGraph(dc, graph, drawMode);
    }

    void OnClose(wxCloseEvent& event) {
        Destroy(); // Usuwa okno i zwalnia pamięć
    }

    void DrawGraph(wxDC& dc, const Graph& graph, int mode) {
        const int width = GetClientSize().GetWidth();
        const int height = GetClientSize().GetHeight();
        const int centerX = width / 2;
        const int centerY = height / 2;
        const int radius = std::min(width, height) / 2.5;

        size_t vertexCount = boost::num_vertices(graph);
        if (vertexCount == 0) return;

        std::vector<wxPoint> vertexPositions(vertexCount);

        if (mode == 1) { // Na okręgu z równymi odstępami
            for (size_t i = 0; i < vertexCount; ++i) {
                double angle = 2 * M_PI * i / vertexCount;
                vertexPositions[i] = wxPoint(
                    centerX + static_cast<int>(radius * cos(angle)),
                    centerY + static_cast<int>(radius * sin(angle))
                );
            }
        } else if (mode == 2) { // Na okręgu losowo
            for (size_t i = 0; i < vertexCount; ++i) {
                double angle = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
                vertexPositions[i] = wxPoint(
                    centerX + static_cast<int>(radius * cos(angle)),
                    centerY + static_cast<int>(radius * sin(angle))
                );
            }
        } else if (mode == 3) { // Wewnątrz okręgu losowo
            for (size_t i = 0; i < vertexCount; ++i) {
                double r = static_cast<double>(rand()) / RAND_MAX * radius;
                double angle = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
                vertexPositions[i] = wxPoint(
                    centerX + static_cast<int>(r * cos(angle)),
                    centerY + static_cast<int>(r * sin(angle))
                );
            }
        }

        // Rysowanie krawędzi
        for (auto e : boost::make_iterator_range(boost::edges(graph))) {
        auto sourceIdx = boost::source(e, graph);
        auto targetIdx = boost::target(e, graph);
        if (sourceIdx < vertexCount && targetIdx < vertexCount) {
        // Obramowanie - czarna linia o większej grubości
        dc.SetPen(wxPen(wxColour(74, 74, 74), 3)); // Czarna linia (obramowanie)
        dc.DrawLine(vertexPositions[sourceIdx], vertexPositions[targetIdx]);

        // Właściwa krawędź - linia w wybranym kolorze
        dc.SetPen(wxPen(wxColour(102, 102, 102), 2)); // Szara linia
        dc.DrawLine(vertexPositions[sourceIdx], vertexPositions[targetIdx]);
    }
}

        // Rysowanie wierzchołków
        size_t index = 0;
        for (auto v : boost::make_iterator_range(boost::vertices(graph))) {
            const auto& vertex = graph[v];
            dc.SetBrush(wxBrush(wxColour(238, 190, 248)));
            dc.DrawCircle(vertexPositions[index], 8);
            dc.DrawText(vertex.label, vertexPositions[index] + wxPoint(10, -10));
            ++index;
        }
    }
};

void GrafyDialog::OnRadioBox1Select(wxCommandEvent& event) {
    int selectedMode = RadioBox1->GetSelection() + 1; // Zakładamy, że opcje są numerowane od 0
}


// Funkcja skalująca współrzędne do zakresu widocznego okna
void ScaleCoordinates(Graph& graph, int width, int height) {
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();

    for (auto v : boost::make_iterator_range(boost::vertices(graph))) {
        minX = std::min(minX, graph[v].x);
        minY = std::min(minY, graph[v].y);
        maxX = std::max(maxX, graph[v].x);
        maxY = std::max(maxY, graph[v].y);
    }

    float scaleX = (width - 20) / (maxX - minX);
    float scaleY = (height - 20) / (maxY - minY);
    float scale = std::min(scaleX, scaleY);

    for (auto v : boost::make_iterator_range(boost::vertices(graph))) {
        graph[v].x = 10 + (graph[v].x - minX) * scale;
        graph[v].y = 10 + (graph[v].y - minY) * scale;
    }
}

void ModifyGraphmlFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        throw std::runtime_error(_("Nie można otworzyć pliku wejściowego: ") + inputFilename);
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string content = buffer.str();

    // Zamiana "directed" na "undirected"
    size_t pos = content.find("<graph edgedefault=\"directed\">");
    if (pos != std::string::npos) {
        content.replace(pos, std::string("<graph edgedefault=\"directed\">").length(), "<graph edgedefault=\"undirected\">");
    }

    // Dodanie brakujących atrybutów
    if (content.find("<key attr.name=\"label\"") == std::string::npos) {
        content.insert(content.find("<graph "), "<key attr.name=\"label\" attr.type=\"string\" for=\"node\" id=\"label\"/>\n");
    }
    if (content.find("<key attr.name=\"weight\"") == std::string::npos) {
        content.insert(content.find("<graph "), "<key attr.name=\"weight\" attr.type=\"double\" for=\"edge\" id=\"weight\"/>\n");
    }

    // Usuwanie niepotrzebnych danych
    const std::vector<std::string> keysToRemove = {"b", "g", "r", "size"};
    for (const auto& key : keysToRemove) {
        size_t pos;
        while ((pos = content.find("<data key=\"" + key + "\">")) != std::string::npos) {
            size_t endPos = content.find("</data>", pos);
            if (endPos != std::string::npos) {
                content.erase(pos, endPos - pos + 7);
            }
        }
    }

    // Usuwanie linii zawierających <data key="v_name"> i <data key="v_type">
    const std::vector<std::string> keysToDelete = {"v_name", "v_type"};
    for (const auto& key : keysToDelete) {
        size_t pos;
        while ((pos = content.find("<data key=\"" + key + "\">")) != std::string::npos) {
            size_t lineStart = content.rfind("\n", pos);  // Znajdź początek linii
            if (lineStart == std::string::npos) {
                lineStart = 0;  // Jeśli nie ma poprzedzającej linii, to początek pliku
            }

            size_t lineEnd = content.find("\n", pos);  // Znajdź koniec linii
            if (lineEnd == std::string::npos) {
                lineEnd = content.length();  // Jeżeli nie ma nowej linii, to koniec pliku
            }

            content.erase(lineStart, lineEnd - lineStart + 1);  // Usuń całą linię
        }
    }

    // Usuwanie linii zawierających "node_color", "node_size", itd.
    const std::vector<std::string> additionalKeysToDelete = {
        "name", "group", "node_color", "node_size", "node_shape", "node_border_color", "node_border_width", "node_opacity", "node_position_x", "node_position_y", "node_weight", "node_type", "ip_address", "mac_address", "node_capacity", "node_bandwidth", "node_status", "description", "vlan_id", "node_utilization", "ports", "node_latency", "node_community", "edge_color", "edge_thickness", "edge_style", "edge_opacity", "edge_weight", "graph_description", "graph_version"

    };
    for (const auto& key : additionalKeysToDelete) {
        size_t pos;
        while ((pos = content.find("<data key=\"" + key + "\">")) != std::string::npos) {
            size_t lineStart = content.rfind("\n", pos);  // Znajdź początek linii
            if (lineStart == std::string::npos) {
                lineStart = 0;  // Jeśli nie ma poprzedzającej linii, to początek pliku
            }

            size_t lineEnd = content.find("\n", pos);  // Znajdź koniec linii
            if (lineEnd == std::string::npos) {
                lineEnd = content.length();  // Jeżeli nie ma nowej linii, to koniec pliku
            }

            content.erase(lineStart, lineEnd - lineStart + 1);  // Usuń całą linię
        }
    }

    // Zamiana <data key="weight"> na <data key="label"> w przypadku znalezienia
    size_t lineStart = 0;
    while ((pos = content.find("<data key=\"weight\">", lineStart)) != std::string::npos) {
        size_t lineEnd = content.find("\n", pos);  // Znajdź koniec linii
        if (lineEnd == std::string::npos) {
            lineEnd = content.length();  // Jeżeli nie ma nowej linii, to koniec pliku
        }

        // Zamiana <data key="weight"> na <data key="label">
        content.replace(pos, std::string("<data key=\"weight\">").length(), "<data key=\"label\">");

        lineStart = lineEnd;  // Przesuń początek wyszukiwania do końca linii
    }

    // Zapisanie zmodyfikowanego pliku
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        throw std::runtime_error(_("Nie można zapisać pliku wyjściowego: ") + outputFilename);
    }
    outputFile << content;
}



void LoadGraph(const std::string& filename) {
    // Resetuj globalny graf przed wczytaniem nowego
    g.clear();  // Wyczyszczenie poprzednich wierzchołków i krawędzi

    // Znajdź rozszerzenie pliku .graphml i zmień nazwę na modified.graphml
    size_t pos = filename.rfind(".graphml");
    if (pos == std::string::npos) {
        throw std::runtime_error("Plik nie ma rozszerzenia .graphml");
    }

    std::string modifiedFilename = filename.substr(0, pos) + "_modified.graphml";

    try {
        ModifyGraphmlFile(filename, modifiedFilename);

        std::ifstream file(modifiedFilename);
        if (!file) {
            throw std::runtime_error(_("Nie można otworzyć zmodyfikowanego pliku: ") + modifiedFilename);
        }

        boost::dynamic_properties dp;
        dp.property("label", boost::get(&VertexProperties::label, g));
        dp.property("x", boost::get(&VertexProperties::x, g));
        dp.property("y", boost::get(&VertexProperties::y, g));
        dp.property("label", boost::get(&EdgeProperties::label, g));

        boost::read_graphml(file, g, dp);

        for (auto e : boost::make_iterator_range(boost::edges(g))) {
            auto source = boost::source(e, g);
            auto target = boost::target(e, g);
            if (!boost::edge(target, source, g).second) {
                boost::add_edge(target, source, g);
            }
        }

        for (auto v : boost::make_iterator_range(vertices(g))) {
            auto& vertex = g[v];
            vertex.x = std::max(0.0f, vertex.x);
            vertex.y = std::max(0.0f, vertex.y);
        }

        for (auto e : boost::make_iterator_range(edges(g))) {
            auto& edge = g[e];
            edge.weight = std::max(1, edge.weight);
        }

        ScaleCoordinates(g, 800, 600);


          file.close();

        //Usuwanie zmodyfikowanego pliku
        if (std::remove(modifiedFilename.c_str()) != 0) {
            throw std::runtime_error(_("Błąd przy usuwaniu pliku: ") + modifiedFilename);
        }

    } catch (const std::exception& e) {
        throw std::runtime_error(_("Błąd podczas wczytywania pliku GraphML: ") + std::string(e.what()));
    }
}






void GrafyDialog::OnButton1Click(wxCommandEvent& event) {
    if (FileDialog1->ShowModal() == wxID_OK) {
        wxString path = FileDialog1->GetPath();
        TextCtrl1->SetValue(path);

        try {
            LoadGraph(std::string(path.mb_str()));
            wxMessageBox("Plik wczytano poprawnie!", "Sukces", wxOK | wxICON_INFORMATION);
        } catch (const std::exception& e) {
            wxMessageBox(wxString::FromUTF8(e.what()), _("Błąd"), wxOK | wxICON_ERROR);
        }
    }
}


// Obsługa przycisku "Rysuj graf"
void GrafyDialog::OnButton2Click(wxCommandEvent& event) {
    if (boost::num_vertices(g) == 0) {
        wxMessageBox("Najpierw wczytaj plik!", _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }

    int mode = RadioBox1->GetSelection() + 1;

    if (mode == 0) {
        wxMessageBox("Wybierz sposób rysowania grafu!", _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }

    GraphWindow* graphWindow = new GraphWindow(this, g, mode);
    graphWindow->Show(true);
}

// Obsługa przycisku "Wyświetl wierzchołki"
void GrafyDialog::OnButton3Click(wxCommandEvent& event) {
    // Sprawdź, czy graf jest pusty
    if (boost::num_vertices(g) == 0) {
        wxMessageBox("Najpierw wczytaj plik!", _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }



    // Przygotuj tekst do wyświetlenia
    std::ostringstream oss;
    for (auto v : boost::make_iterator_range(boost::vertices(g))) {
        const auto& vertex = g[v];
        oss << "Wierzchołek: " << vertex.label
            << ", Pozycja: (" << vertex.x << ", " << vertex.y << ")\n";
    }

    // Wyświetl wierzchołki w oknie dialogowym
    wxMessageBox(wxString::FromUTF8(oss.str().c_str()), _("Wierzchołki grafu"), wxOK | wxICON_INFORMATION);
}

void GrafyDialog::OnButton4Click(wxCommandEvent& event) {
    // Sprawdź, czy graf jest pusty
    if (boost::num_edges(g) == 0) {
        wxMessageBox(_("Graf nie zawiera żadnych krawędzi!"), _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }

    // Przygotuj tekst do wyświetlenia
    std::ostringstream oss;
    for (auto e : boost::make_iterator_range(boost::edges(g))) {
        const auto& edge = g[e];
        const auto& source = g[boost::source(e, g)];
        const auto& target = g[boost::target(e, g)];

        oss << "Krawędź: " << edge.label
            << ", Od: " << source.label
            << ", Do: " << target.label
            << "\n";
    }

    // Wyświetl krawędzie w oknie dialogowym
    wxMessageBox(wxString::FromUTF8(oss.str().c_str()), _("Krawędzie grafu"), wxOK | wxICON_INFORMATION);
}

void GrafyDialog::OnButton5Click(wxCommandEvent& event) {
    if (boost::num_vertices(g) == 0) {
        wxMessageBox("Najpierw wczytaj plik!", _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }

    bool is_directed = boost::is_directed(g);
    bool has_weights = false;
    bool is_complete = false;
    bool is_cyclic = false;
    bool is_bipartite = false;
    bool is_tree = false;
    bool is_forest = false;
    bool is_planar = false;

    // Sprawdzanie, czy krawędzie mają wagi
    for (auto e : boost::make_iterator_range(boost::edges(g))) {
        if (g[e].weight != 1) {
            has_weights = true;
        }
    }

    size_t vertex_count = boost::num_vertices(g);
    size_t edge_count = boost::num_edges(g);

    // Sprawdzanie, czy graf jest pełny
    is_complete = edge_count == (vertex_count * (vertex_count - 1)) / 2;

    //Sprawdzanie spójności
    std::vector<int> component_map(vertex_count);
    int num_components = boost::connected_components(g, &component_map[0]);
    bool is_connected = num_components == 1;

    // Sprawdzanie cykliczności grafu
    if (edge_count > vertex_count - 1) {
        std::vector<int> color_map(vertex_count);
        try {
            boost::breadth_first_search(g, *boost::vertices(g).first,
                                        boost::visitor(boost::bfs_visitor<boost::null_visitor>())
                                        .color_map(boost::make_iterator_property_map(color_map.begin(), get(boost::vertex_index, g))));
        } catch (boost::not_a_dag&) {
            is_cyclic = true;
        }
    }

    // Sprawdzanie dwudzielności grafu
    std::vector<int> color_map(vertex_count, -1); // -1 oznacza brak przypisania koloru
    for (auto v : boost::make_iterator_range(boost::vertices(g))) {
        if (color_map[v] == -1) {
            std::queue<int> q;
            color_map[v] = 0;
            q.push(v);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (auto e : boost::make_iterator_range(boost::out_edges(u, g))) {
                    int neighbor = boost::target(e, g);
                    if (color_map[neighbor] == -1) {
                        color_map[neighbor] = 1 - color_map[u]; // Przypisz przeciwny kolor
                        q.push(neighbor);
                    } else if (color_map[neighbor] == color_map[u]) {
                        is_bipartite = false; // Jeśli są dwa sąsiadujące wierzchołki o tym samym kolorze, graf nie jest dwudzielny
                        break;
                    }
                }

                if (!is_bipartite) break;
            }
        }

        if (!is_bipartite) break;
    }

    // Sprawdzanie, czy graf jest drzewem i lasem
    is_tree = (is_connected && edge_count == vertex_count - 1);
    is_forest = !is_cyclic;

    // Sprawdzanie, czy graf jest planar
    is_planar = boost::boyer_myrvold_planarity_test(g);  // Sprawdzanie planarity za pomocą boost::boyer_myrvold_planarity_test

    // Przygotowanie wyniku do wyświetlenia
    std::ostringstream oss;
    oss << "Graf pełny: " << (is_complete ? "Tak" : "Nie") << "\n";
    oss << "Graf spójny: " << (is_connected ? "Tak" : "Nie") << "\n";
    oss << "Graf cykliczny: " << (is_cyclic ? "Tak" : "Nie") << "\n";
    oss << "Graf dwudzielny: " << (is_bipartite ? "Tak" : "Nie") << "\n";
    oss << "Drzewo: " << (is_tree ? "Tak" : "Nie") << "\n";
    oss << "Las: " << (is_forest ? "Tak" : "Nie") << "\n";
    oss << "Graf planarny: " << (is_planar ? "Tak" : "Nie") << "\n";

    wxMessageBox(wxString::FromUTF8(oss.str().c_str()), "Informacje o grafie", wxOK | wxICON_INFORMATION);
}


void GrafyDialog::OnButton6Click1(wxCommandEvent& event) {
    if (boost::num_vertices(g) == 0) {
        wxMessageBox("Najpierw wczytaj plik!", _("Błąd"), wxOK | wxICON_WARNING);
        return;
    }

    wxTextEntryDialog dialog(this, _("Podaj etykietę wierzchołka początkowego:"), _("Najkrótsze ścieżki"));
    if (dialog.ShowModal() != wxID_OK) {
        return;
    }

    std::string startLabel = std::string(dialog.GetValue().mb_str());
    boost::graph_traits<Graph>::vertex_descriptor startVertex;
    bool found = false;

    for (auto v : boost::make_iterator_range(boost::vertices(g))) {
        if (g[v].label == startLabel) {
            startVertex = v;
            found = true;
            break;
        }
    }

    if (!found) {
        wxMessageBox(_("Nie znaleziono wierzchołka o podanej etykiecie!"), _("Błąd"), wxOK | wxICON_ERROR);
        return;
    }

    std::unordered_map<boost::graph_traits<Graph>::vertex_descriptor, int> distances;
    std::unordered_map<boost::graph_traits<Graph>::vertex_descriptor, boost::graph_traits<Graph>::vertex_descriptor> predecessors;
    std::priority_queue<std::pair<int, boost::graph_traits<Graph>::vertex_descriptor>, std::vector<std::pair<int, boost::graph_traits<Graph>::vertex_descriptor>>, std::greater<>> pq;

    for (auto v : boost::make_iterator_range(boost::vertices(g))) {
        distances[v] = std::numeric_limits<int>::max();
    }

    distances[startVertex] = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        auto [dist, currentVertex] = pq.top();
        pq.pop();

        if (dist > distances[currentVertex]) {
            continue;
        }

        for (auto edge : boost::make_iterator_range(boost::out_edges(currentVertex, g))) {
            auto neighbor = boost::target(edge, g);
            int weight = 1;//Każda krawędź ma wagę 1, liczymy liczbę krawędzi

            if (distances[currentVertex] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currentVertex] + weight;
                predecessors[neighbor] = currentVertex;
                pq.push({distances[neighbor], neighbor});
            }
        }
    }

    std::ostringstream oss;
    oss << "Najkrótsze ścieżki od wierzchołka: " << startLabel << "\n\n";
    for (auto v : boost::make_iterator_range(boost::vertices(g))) {
        oss << "Do wierzchołka " << g[v].label << ": ";
        if (distances[v] == std::numeric_limits<int>::max()) {
            oss << "Brak połączenia\n";
        } else {
            oss << distances[v] << "\n";
        }
    }

    wxMessageBox(wxString::FromUTF8(oss.str().c_str()), _("Najkrótsze ścieżki"), wxOK | wxICON_INFORMATION);
}
