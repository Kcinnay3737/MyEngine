let project = new Project("BOI");

project.kore = false;

project.addFiles(
    "BOI/**",
    "External/AI-Toolbox/src/Seeder.cpp",
    "External/AI-Toolbox/src/Utils/Adam.cpp",
    "External/AI-Toolbox/src/Utils/Combinatorics.cpp",
    "External/AI-Toolbox/src/Utils/IO.cpp",
    "External/AI-Toolbox/src/Utils/Probability.cpp",
    "External/AI-Toolbox/src/Utils/Polytope.cpp",
    "External/AI-Toolbox/src/Utils/StorageEigen.cpp",
    "External/AI-Toolbox/src/Utils/LP/LpSolveWrapper.cpp",
    "External/AI-Toolbox/src/Tools/Statistics.cpp",
    "External/AI-Toolbox/src/Tools/CassandraParser.cpp",
    "External/AI-Toolbox/src/Bandit/Experience.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/EpsilonPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/RandomPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/QGreedyPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/QSoftmaxPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/ThompsonSamplingPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/TopTwoThompsonSamplingPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/T3CPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/SuccessiveRejectsPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/LRPPolicy.cpp",
    "External/AI-Toolbox/src/Bandit/Policies/ESRLPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Experience.cpp",
    "External/AI-Toolbox/src/MDP/Utils.cpp",
    "External/AI-Toolbox/src/MDP/Model.cpp",
    "External/AI-Toolbox/src/MDP/SparseExperience.cpp",
    "External/AI-Toolbox/src/MDP/SparseModel.cpp",
    "External/AI-Toolbox/src/MDP/IO.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/QLearning.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/RLearning.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/DoubleQLearning.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/HystereticQLearning.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/SARSA.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/ExpectedSARSA.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/SARSAL.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/ValueIteration.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/PolicyIteration.cpp",
    "External/AI-Toolbox/src/MDP/Algorithms/Utils/OffPolicyTemplate.cpp",
    "External/AI-Toolbox/src/MDP/Policies/PolicyWrapper.cpp",
    "External/AI-Toolbox/src/MDP/Policies/Policy.cpp",
    "External/AI-Toolbox/src/MDP/Policies/EpsilonPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Policies/QPolicyInterface.cpp",
    "External/AI-Toolbox/src/MDP/Policies/QGreedyPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Policies/QSoftmaxPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Policies/WoLFPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Policies/PGAAPPPolicy.cpp",
    "External/AI-Toolbox/src/MDP/Environments/Utils/GridWorld.cpp",
);

project.setDebugDir("Deployment");

project.addIncludeDir("./TheEngine/Includes");
project.addIncludeDir("./External/AI-Toolbox/include");
project.addIncludeDir("./BOI/Includes");



project.setCppStd("c++20");

project.flatten();

const otherproj = await project.addProject("TheEngine");
otherproj.addProvider(project, true);

resolve(project);