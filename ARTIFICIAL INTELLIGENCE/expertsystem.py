def job_asking_expert_system():
    print("Job Recommendation Expert System")
    print("Please answer the following questions to help us recommend a job for you.\n")
    
    skill_level = input("What is your skill level? (beginner/intermediate/advanced): ").strip().lower()
    interest_field = input("Which field interests you most? (tech/health/education/business/creative): ").strip().lower()
    work_env = input("What type of work environment do you prefer? (remote/office/hybrid): ").strip().lower()
    salary_expectation = input("What is your salary expectation? (low/medium/high): ").strip().lower()
    
    print("\nAnalyzing your preferences...\n")
    # Recommendations
    if skill_level == "beginner":
        if interest_field == "tech":
            print("Recommended job: IT Support, Junior Web Developer")
        elif interest_field == "health":
            print("Recommended job: Medical Assistant, Lab Technician")
        elif interest_field == "education":
            print("Recommended job: Teaching Assistant, Tutor")
        elif interest_field == "business":
            print("Recommended job: Sales Associate, Customer Service Representative")
        elif interest_field == "creative":
            print("Recommended job: Content Writer, Graphic Design Intern")
    elif skill_level == "intermediate":
        if interest_field == "tech":
            print("Recommended job: Software Engineer, Data Analyst")
        elif interest_field == "health":
            print("Recommended job: Registered Nurse, Physical Therapist")
        elif interest_field == "education":
            print("Recommended job: School Teacher, Curriculum Designer")
        elif interest_field == "business":
            print("Recommended job: Marketing Executive, HR Specialist")
        elif interest_field == "creative":
            print("Recommended job: Video Editor, UX Designer")
    else:  # advanced
        if interest_field == "tech":
            if work_env == "remote" and salary_expectation == "high":
                print("Recommended job: Senior Cloud Architect, Machine Learning Engineer")
            else:
                print("Recommended job: Technical Lead, Solutions Architect")
        elif interest_field == "health":
            print("Recommended job: Doctor, Medical Researcher")
        elif interest_field == "education":
            print("Recommended job: University Professor, Principal")
        elif interest_field == "business":
            print("Recommended job: Business Consultant, Operations Director")
        elif interest_field == "creative":
            print("Recommended job: Creative Director, Senior Copywriter")

job_asking_expert_system()