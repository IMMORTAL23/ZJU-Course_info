
# PlanAhead Launch Script for Post-Synthesis floorplanning, created by Project Navigator

create_project -name NeverGiveUp -dir "E:/logic/NeverGiveUp/planAhead_run_1" -part xc7k160tffg676-2L
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "E:/logic/NeverGiveUp/main.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {E:/logic/NeverGiveUp} }
set_property target_constrs_file "Constraints.ucf" [current_fileset -constrset]
add_files [list {Constraints.ucf}] -fileset [get_property constrset [current_run]]
link_design
