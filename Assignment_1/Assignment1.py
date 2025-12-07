import pandas as pd
import os
import glob

def get_groups(df):
    df.dropna(inplace=True,axis=1)
    df['Branch']=df['Roll'].str.extract(r"\d+([a-zA-Z]{2})\d+")
    grouped=df.groupby('Branch')

    branch_dict = {branch: data.to_dict("records") for branch, data in grouped}
    branch_idx = {idx: 0 for idx in branch_dict}
    
    return grouped,branch_dict,branch_idx

def save_to_csv(dataframe,file_name,save_location):
    if not os.path.exists(save_location):
        os.makedirs(save_location)
    dataframe.to_csv(os.path.join(save_location, file_name)+'.csv',index=False)

def save_branchwise(df,save_location):
    grouped,_,_=get_groups(df)
    
    for grouped_branch,grouped_branch_df in grouped:
        save_to_csv(grouped_branch_df,grouped_branch,os.path.join(save_location, 'branchwise_full_list'))
        


def shullfe_records(df,mode,num_groups,save_location):
    
    _,branch_dict,branch_idx=get_groups(df)
    
    groups = [[] for _ in range(num_groups)]
    grp_idx = 0

    if mode == "branch_wise":
        branch_order = list(branch_dict.keys())

        while any(branch_idx[b] < len(branch_dict[b]) for b in branch_order):
            for stream in branch_order:
                if branch_idx[stream] < len(branch_dict[stream]): 
                    student = branch_dict[stream][branch_idx[stream]]
                    branch_idx[stream] += 1
                    groups[grp_idx % num_groups].append(student)
            grp_idx += 1   

    elif mode == "uniform":
        all_ordered_branch = []
        branch_order = sorted(branch_dict.keys(), key=lambda b: len(branch_dict[b]), reverse=True)
        
        for branch in branch_order:
            all_ordered_branch.extend(branch_dict[branch])
    
        totalstud_all_branches = len(all_ordered_branch)
        student_per_grp = totalstud_all_branches // num_groups
        rem = totalstud_all_branches % num_groups
        
        start = 0
        for i in range(num_groups):
            group_size = student_per_grp + (1 if i < rem else 0)
            group_students = all_ordered_branch[start : start + group_size]
            start += group_size
            groups[i] = group_students
    
   
    for i, group in enumerate(groups, start=1):
        if group:
            save_to_csv(pd.DataFrame(group),f"{mode}_group{i}",os.path.join(save_location, f'{mode}'))
            



def generate_summary(root,folder_group):
    li = []

    
    for mode in folder_group:
        folder = os.path.join(root, mode)
        '''if not os.path.exists(folder):
            continue'''
        
        for csv_path in glob.glob(os.path.join(folder, "*.csv")):
            df=pd.read_csv(csv_path)

            branch_counts = df['Branch'].value_counts().to_dict()
            totalstud_all_branches = len(df)

            record = {"Group Name": f"{mode}_{os.path.splitext(os.path.basename(csv_path))[0]}", 
                        "Total Students": totalstud_all_branches}
            record.update(branch_counts)

            li.append(record)

    summary_df = pd.DataFrame(li)
    summary_df.fillna(0, inplace=True)

    sorted_branch = sorted([cols for cols in list(summary_df.columns) if cols not in ["Group Name", "Total Students"]])
    summary_df = summary_df[["Group Name"] + sorted_branch + ["Total Students"]]
    save_to_csv(summary_df,"Summary",os.path.join(root, 'Summary'))

