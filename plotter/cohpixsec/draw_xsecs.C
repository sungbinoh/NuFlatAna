#include "canvas_margin.h"
#include "mylib.h"

int N_samples = 3;
TString sample_names[] = {"GENIE_G21_11a", "GENIE_G18_01a", "GENIE_G18_02a"};
TString sample_names_for_leg[] = {"GENIE (G21_11a)", "GENIE (G18_01a)", "GENIE (G18_012)"}; 
Int_t color_array[] = {632, 800, 867, 600, 416, 901, 432, 400, 920};
Int_t line_sty_array[] = {1, 1, 7};

int N_vars = 7;
TString hist_names[] = {"PiCos", "MuCos", "MuPiOpenCos",
			"PiE", "MuE",
			"Abst", "AbstApprox",
};
TString var_names[] = {"cos#theta_{#pi^{+}}", "cos#theta_{#mu^{-}}", "cos#theta(#mu^{-}, #pi^{+})",
		       "E_{#pi^{+}}", "E_{#mu^{-}}",
		       "|t|", "|t_{Appr.}|",
};
TString var_units[] = {"", "", "",
		       "[GeV]", "[GeV]",
		       "[GeV/c]^2", "[GeV/c]^2",
};
int rebins[] = {5, 5, 5,
		5, 5,
		1, 1,
};
double x_mins[] = {0., 0., -1.,
		   0., 0.,
		   0., 0.,
};
double x_maxs[] = {1., 1., 1.,
		   3., 3.,
		   0.2, 0.2,
};


TString root_file_dir = getenv("NuFlatAna_WD");
root_file_dir = root_file_dir + "/output/root/";
TString out_plot_dir = getenv("NuFlatAna_WD");
out_plot_dir = out_plot_dir + "/output/plot/";

void draw_each_var(TString hist_name, TString var_name, TString var_unit, int rebin, double x_min, double x_max){

  double max_y = -1.;
  TString this_hist_name = "COH" + hist_name;
  for(int i = 0; i < N_samples; i++){
    TString this_file_path = root_file_dir + "hists_" + sample_names[i] + ".root";
    TFile *this_f =new TFile(this_file_path);

    if((TH1D*)gDirectory -> Get(this_hist_name)){
      maphist[sample_names[i] + this_hist_name] = (TH1D*)gDirectory -> Get(this_hist_name) -> Clone();
      maphist[sample_names[i] + this_hist_name] -> Rebin(rebin);
      maphist[sample_names[i] + this_hist_name] = Add_Under_and_Overflow(maphist[sample_names[i] + this_hist_name]);
      double this_max_y = maphist[sample_names[i] + this_hist_name] -> GetMaximum();
      if(this_max_y > max_y) max_y = this_max_y;
    }
    else{
      cout << "[draw_each_var] nullptr for " << sample_names[i] << ", " << this_hist_name << endl;
      maphist[sample_names[i] + this_hist_name] = nullptr;
    }
  }

  TCanvas *c = new TCanvas("", "", 1600, 1600);
  canvas_margin(c);
  //gStyle -> SetOptStat(1111);

  // == Top pad
  TPad *pad_1 = new TPad("", "", 0, 0.25, 1, 1);
  pad_1 -> SetTopMargin( 0.07 );
  pad_1 -> SetBottomMargin( 0.05 );
  pad_1 -> SetLeftMargin( 0.15 );
  pad_1 -> SetRightMargin( 0.03 );
  pad_1 -> Draw();
  pad_1 -> cd();

  TH1D *pad1_template = new TH1D("", "", 1, x_min, x_max);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(3);
  pad1_template -> SetStats(0);
  pad1_template -> GetXaxis() -> SetLabelSize(0);
  pad1_template -> GetXaxis() -> SetTitleSize(0);
  pad1_template -> GetYaxis() -> SetLabelSize(0.05);
  pad1_template -> GetYaxis() -> SetTitleSize(0.05);
  pad1_template -> GetYaxis() -> SetTitleOffset(1.3);
  pad1_template -> GetYaxis() -> SetTitle("#frac{d#sigma}{d" + var_name + "} [10^{-39} cm^{2}/Nucleon]");
  pad1_template -> GetYaxis() -> SetRangeUser(0., max_y * 1.8);
  pad1_template -> Draw("hist");

  TLegend *l_pad1 = new TLegend(0.20, 0.70, 0.90, 0.90);
  l_pad1 -> SetFillColor(kWhite);
  l_pad1 -> SetLineColor(kWhite);
  l_pad1 -> SetBorderSize(1);
  l_pad1 -> SetFillStyle(4000);
  l_pad1 -> SetShadowColor(0);
  l_pad1 -> SetEntrySeparation(0.3);
  l_pad1 -> SetNColumns(3);

  for(int i = 0; i < N_samples; i++){
    TString this_hist_key = sample_names[i] + this_hist_name;
    if(maphist[this_hist_key] != nullptr){
      maphist[this_hist_key] -> SetLineWidth(2);
      maphist[this_hist_key] -> SetLineColor(color_array[i]);
      maphist[this_hist_key] -> SetLineStyle(line_sty_array[i]);
      maphist[this_hist_key] -> Draw("histsame");
      l_pad1 -> AddEntry(maphist[this_hist_key], sample_names_for_leg[i], "l");
    }
  }

  l_pad1 -> Draw("same");
  gPad->RedrawAxis();

  // == Bottom pad
  c -> cd();
  TPad *pad_2 = new TPad("", "", 0, 0, 1, 0.25);
  pad_2 -> SetTopMargin( 0.05 );
  pad_2 -> SetBottomMargin( 0.4 );
  pad_2 -> SetLeftMargin( 0.15 );
  pad_2 -> SetRightMargin( 0.03 );
  pad_2 -> Draw();
  pad_2 -> cd();
  TH1D * pad2_template = new TH1D("", "", 1, x_min, x_max);
  gStyle->SetOptTitle(0);
  gStyle->SetLineWidth(2);
  pad2_template -> Draw("hist");
  pad2_template -> SetTitle("");
  pad2_template -> SetLineColor(kWhite);
  pad2_template -> GetXaxis() -> SetTitle(var_name + " " + var_unit);
  pad2_template -> GetXaxis() -> SetTitleSize(0.15);
  pad2_template -> GetXaxis() -> SetLabelSize(0.125);
  pad2_template -> GetYaxis() -> SetTitle("#frac{Sample}{" + sample_names_for_leg[0] + "}");
  pad2_template -> GetYaxis() -> SetTitleSize(0.08);
  pad2_template -> GetYaxis() -> SetTitleOffset(0.5);
  pad2_template -> GetYaxis() -> SetLabelSize(0.09);
  pad2_template -> GetYaxis() -> SetNdivisions(505);
  pad2_template -> GetYaxis() -> SetRangeUser(0.0, 5.0);
  pad2_template -> SetStats(0);
  pad2_template -> Draw("histsame");

  TLegend *l_pad2 = new TLegend(0.2, 0.85, 0.6, 0.95);
  l_pad2 -> SetBorderSize(0);
  l_pad2 -> SetNColumns(2);

  for(int i = 1; i < N_samples; i++){
    TString this_hist_key = sample_names[i] + this_hist_name;
    TH1D * this_ratio = (TH1D*)maphist[this_hist_key] -> Clone();
    this_ratio -> Divide(maphist[sample_names[0] + this_hist_name]);
    this_ratio -> Draw("histsame");
    l_pad2 -> AddEntry(this_ratio, sample_names[i], "l");
  }
  
  l_pad2 -> Draw("same");
  gPad->RedrawAxis();

  // == Latex
  c -> cd();

  // == Save
  TString output_path = out_plot_dir + "/cohpi/" + hist_name + ".pdf";
  c -> SaveAs(output_path);

  c -> Close();
}

void draw_xsecs(){

  setTDRStyle();

  for(int i = 0; i < N_vars; i++){
    draw_each_var(hist_names[i], var_names[i], var_units[i], rebins[i], x_mins[i], x_maxs[i]);
  }
}


  
