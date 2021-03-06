#ifndef NTTINY_PLOTS_H
#define NTTINY_PLOTS_H

#include "defs.h"
#include "api.h"

#include <implot.h>
#include <toml.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

namespace nttiny {

struct PlotMetadata {
  int m_ID;
  std::string m_type;
  bool m_log;
  float m_vmin, m_vmax;
  std::string m_cmap;
  int m_field_selected;

  void writeToFile(const std::string& fname, bool rewrite = false) {
    const toml::value data{{"ID", m_ID},
                           {"type", m_type},
                           {"log", m_log},
                           {"vmin", m_vmin},
                           {"vmax", m_vmax},
                           {"cmap", m_cmap},
                           {"field_selected", m_field_selected}};
    std::ofstream export_file;
    if (rewrite) {
      export_file.open(fname);
    } else {
      export_file.open(fname, std::fstream::app);
    }
    if (export_file.is_open()) {
      export_file << "[Plot." << m_ID << "]\n";
      export_file << data;
      export_file << "\n";
      export_file.close();
    } else {
      throw std::runtime_error("ERROR: Cannot open file.");
    }
  }
};

template <class T>
class Ax {
protected:
  SimulationAPI<T>* m_sim;
  const int m_ID;

public:
  Ax(int id) : m_ID(id) {}
  virtual ~Ax() = default;
  virtual auto draw() -> bool { return false; }
  virtual auto getId() -> int { return -1; }
  virtual auto exportMetadata() -> PlotMetadata { return PlotMetadata(); }
  virtual void importMetadata(const PlotMetadata&){};
  void bindSimulation(SimulationAPI<T>* sim) { this->m_sim = sim; }
};

template <class T>
class Plot2d : public Ax<T> {
protected:
  float m_scale{1.0f};
  float m_plot_size{20.0f * ImGui::GetFontSize()};

public:
  Plot2d(int id) : Ax<T>(id) {}
  ~Plot2d() override = default;
  void scale();
  auto close() -> bool;
  auto getId() -> int override { return this->m_ID; }
  void outlineDomain(std::string field_selected = "");
};

template <class T>
class Pcolor2d : public Plot2d<T> {
protected:
  float m_sidebar_w{5.0f * ImGui::GetFontSize()}, m_cmap_h{20.0f * ImGui::GetFontSize()};
  bool m_log{false};
  float m_vmin, m_vmax;
  ImPlotColormap m_cmap{ImPlotColormap_Jet};
  int m_field_selected{0};

public:
  Pcolor2d(int id, float vmin, float vmax) : Plot2d<T>(id), m_vmin(vmin), m_vmax(vmax) {}
  ~Pcolor2d() override = default;
  auto draw() -> bool override;
  auto exportMetadata() -> PlotMetadata override;
  void importMetadata(const PlotMetadata&) override;
};

template <class T>
class Scatter2d : public Plot2d<T> {
protected:
  bool* m_prtl_enabled{nullptr};
  const char** m_prtl_names;

public:
  Scatter2d(int id) : Plot2d<T>(id) {}
  ~Scatter2d() override = default;
  auto draw() -> bool override;
  auto exportMetadata() -> PlotMetadata override;
  void importMetadata(const PlotMetadata&) override;
};

// TODO: 1d plot, linear, log linear and log log, multiple data

} // namespace nttiny

#endif
