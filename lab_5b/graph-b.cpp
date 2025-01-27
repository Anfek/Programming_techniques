#include "graph-b.h"

Graph_b::Edges::Edges(int a, int b, int len){
    this->start = a;
    this->end = b;
    this->lenght = len;
}

Graph_b::Graph_b():Graph(){}

Graph_b::Visit_Stack Graph_b::dfs_inv(Visit_Stack VS, int x){
    VS.visit[x] = true;

    for(auto iter = graph[x].begin(); iter != graph[x].end(); iter++)
        if(VS.visit[(*iter).get_numb()]==false)
            VS = dfs_inv(VS, (*iter).get_numb());
    VS.stack.push_back(x);
    return VS;
}

void Graph_b::Tarjan_algorithm(){
    Visit_Stack VS;
    VS.visit.resize(graph.size());
    for (int i = 0; i < graph.size(); i++)
        VS.visit[i]=false;
    for (int i = 0; i < graph.size(); i++)
        if(VS.visit[i]==false)
            VS = dfs_inv(VS, i);
    
    std::cout<<"Tarjan's algorithm:"<<std::endl;
    for (int i = VS.stack.size()-1; i>=0 ; i--)
        std::cout<< VS.stack[i]+1 << "\t";
    std::cout<<"\n"<<std::endl;
}

int Graph_b::search_len(int a, int b, Graph_b::cycle_search_assistant CSA){
    int len;
    for (int i = 0; i < CSA.g[a].size(); i++){
        if(CSA.g[a][i].first == b){
            len = CSA.g[a][i].second;
        }
    }
    return len;
}


Graph_b::cycle_search_assistant Graph_b::add_cycle(int cycle_end, int cycle_st, Graph_b::cycle_search_assistant CSA){
    CSA.cycle[CSA.ncycle].clear();
    int buf;
	CSA.cycle[CSA.ncycle].push_back(std::make_pair(cycle_st, search_len(cycle_st, cycle_end, CSA)));
    buf = cycle_st;
	for(int v = cycle_end; v != cycle_st; v = CSA.p[v]){
		CSA.cycle[CSA.ncycle].push_back(std::make_pair(v, search_len(buf, v, CSA)));
        buf = v;//предыдущий элемент
    }
	CSA.cycle[CSA.ncycle].push_back(std::make_pair(cycle_st, search_len(buf, cycle_st, CSA)));
	
	std::reverse(CSA.cycle[CSA.ncycle].begin(), CSA.cycle[CSA.ncycle].end());
    return CSA;
}

Graph_b::cycle_search_assistant Graph_b::dfs(Graph_b::cycle_search_assistant CSA, int v){
    CSA.color[v] = 1;
	for(int i = 0; i < CSA.g[v].size(); i++) {
		int to = CSA.g[v][i].first;
        int len = CSA.g[v][i].second;
		if(CSA.color[to] == 0){
			CSA.p[to] = v;
			CSA = dfs(CSA, to);
		}
		else if(CSA.color[to] == 1){
            CSA = add_cycle(v, to, CSA);

            
			if(CSA.cycle[CSA.ncycle].size() > 3) {// Исключение вырожденных случаев, н: 1 2 1
                CSA.ncycle++; 
                CSA.cycle.resize(CSA.cycle.size()+1);
            }
        }
	}
	CSA.color[v] = 2;
    return CSA;
}

std::vector<Graph_b::Edges*> Graph_b::find_cycles(std::vector<Graph_b::Edges*> edges){
    cycle_search_assistant CSA;
    CSA.color.assign(graph.size(), 0);
    CSA.p.assign(graph.size(), -1);
    CSA.cycle.resize(1);
    CSA.g.resize(graph.size());
    CSA.ncycle = 0;

    for (int i = 0; i < edges.size(); i++){
        CSA.g[edges[i]->start].push_back(std::make_pair(edges[i]->end, edges[i]->lenght));
        CSA.g[edges[i]->end].push_back(std::make_pair(edges[i]->start, edges[i]->lenght));
    }
    
    
    for(int i = 0; i < CSA.color.size(); i++)
		if(CSA.color[i] == 0)
			CSA = dfs(CSA, i);
            
    
    std::vector<Edges*> result_cycle;
    for (int i = 0; i < CSA.cycle.size()-1; i++){
        for (int j = 0; j < CSA.cycle[i].size()-1; j++){
            bool repeat = false;
            for (int k = 0; k < result_cycle.size(); k++){
                bool ch1 = CSA.cycle[i][j].first == result_cycle[k]->start && CSA.cycle[i][j+1].first == result_cycle[k]->end;
                bool ch2 = CSA.cycle[i][j].first == result_cycle[k]->end && CSA.cycle[i][j+1].first == result_cycle[k]->start;
                if(ch1||ch2){
                    repeat = true;
                    break;
                }
            }
            if(repeat == false){
                result_cycle.push_back(new Edges(CSA.cycle[i][j].first, CSA.cycle[i][j+1].first, CSA.cycle[i][j+1].second));
            }
        }
    }

    return result_cycle;
}

bool Graph_b::graph_vertices(std::vector<int> peaks, int i){
    if(peaks.size()>1){
        for (int i = 0; i < peaks.size(); i++){
            for (int j = i+1; j < peaks.size(); j++){
                if(i!=j && peaks[i]==peaks[j])
                    return false;
            }
        }
    }
    if(peaks.size() == graph.size())
        return true;

    bool check = false;
    peaks.push_back(i);
    for(auto iter = graph[i].begin(); iter!=graph[i].end(); iter++){
        check = check || graph_vertices(peaks, (*iter).get_numb());
    }
    return check;
}

bool Graph_b::connectivity_check(std::vector<Graph_b::Edges*> edges){
    std::vector<int> peaks;
    bool check = false;
    for (int i = 0; i < graph.size(); i++){
        check = check || graph_vertices(peaks, i);
        if(check)
            return check;
    }
    return check;
}

std::vector<Graph_b::Edges*> Graph_b::Graph_to_edges_Euler_check(std::string algorithm){
    std::vector<std::vector<int>> arr = list_to_matrix();
    std::vector<Edges*> empty_array;
    std::vector<Edges*> edges;
    for (int i = 0; i < graph.size(); i++) {
        if(graph[i].size()%2 != 0){
            std::cout<<algorithm<<std::endl;
            std::cout<<"The degree of the vertex "<<i+1<<" is odd - there is no Euler cycle"<<std::endl;
            std::cout<<std::endl;
            return empty_array;
        }
        for (int j = i; j < graph.size(); j++) {
            if (arr[i][j] != (int)INFINITY) {
                edges.push_back(new Edges(i, j, arr[i][j]));
            }
        }
    }

    if(!connectivity_check(edges)){
        std::cout<<algorithm<<std::endl;
        std::cout<<"The graph is not connected"<<std::endl;
        std::cout<<std::endl;
        return empty_array;
    }

    return edges;
}

void Graph_b::Fleury_algorithm(){
    std::vector<Edges*> edges = Graph_to_edges_Euler_check("Fleury's algorithm:");
    if(edges.size()==0)
        return;
        
    std::vector<Edges*> Result;
    int numbers_edge = edges.size();
    int x = 0;
    for (int i = 0; i < numbers_edge; i++){
        std::vector<std::pair<Edges*, std::vector<Edges*>::iterator>> edges_containing_x; //все рёбра инцедентные вершине x
        for(auto iter = edges.begin(); iter!=edges.end(); iter++){
            if((*iter)->start == x || (*iter)->end == x)
                edges_containing_x.push_back(std::make_pair(new Edges((*iter)->start, (*iter)->end, (*iter)->lenght), iter));
        }
        
        if(edges_containing_x.size() == 1){ //если ребро единственное - добавляем его в результат
            auto iter = edges_containing_x[0].second;
            if(edges_containing_x[0].first->start == x)
                Result.push_back(new Edges((*iter)->start, (*iter)->end, (*iter)->lenght));
            else
                Result.push_back(new Edges((*iter)->end, (*iter)->start, (*iter)->lenght));
            edges.erase(iter); //удаляем ребро из графа
            x = Result[Result.size()-1]->end;
        }
        else if (edges_containing_x.size() > 1){
            std::vector<bool> in_cycle;
            in_cycle.assign(edges_containing_x.size(), false);
            std::vector<Edges*> cycles = find_cycles(edges); //находим все циклы
            for (int i = 0; i < edges_containing_x.size(); i++){
                for (int j = 0; j < cycles.size(); j++){
                    bool ch1 = edges_containing_x[i].first->start == cycles[j]->start && edges_containing_x[i].first->end == cycles[j]->end;
                    bool ch2 = edges_containing_x[i].first->start == cycles[j]->end && edges_containing_x[i].first->end == cycles[j]->start;
                    if(ch1 || ch2){
                        in_cycle[i] = true;
                        break;
                    }
                }
                if (in_cycle[i] == true){
                    auto iter = edges_containing_x[i].second;
                    if(edges_containing_x[i].first->start == x)
                        Result.push_back(new Edges((*iter)->start, (*iter)->end, (*iter)->lenght));
                    else
                        Result.push_back(new Edges((*iter)->end, (*iter)->start, (*iter)->lenght));
                    edges.erase(iter);
                    break;
                }
            } 
            x = Result[Result.size()-1]->end;
        }
        else{
            if(Result.size()!=0 && x!=Result[Result.size()-1]->start)
                x = Result[Result.size()-1]->start;
            else
                x=(x+1)%graph.size();
            i--;
        }        
    }

    std::cout<<"Fleury's algorithm:"<<std::endl;
    if(numbers_edge == Result.size()){
        for (int i = 0; i < Result.size(); i++)
            std::cout<<Result[i]->start+1<<", ";
        std::cout<<Result[Result.size()-1]->end+1<<std::endl;
        for (int i = 0; i < Result.size(); i++)
            std::cout<<"("<<Result[i]->start+1<<", "<<Result[i]->end+1<<", len="<<Result[i]->lenght<<")"<<std::endl;
    }
    else
        std::cout<<"The graph is not connected"<<std::endl;

    std::cout<<std::endl;    
}

std::pair<std::vector<Graph_b::Edges*>, std::vector<int>> Graph_b::FindEulerPath(std::pair<std::vector<Graph_b::Edges*>, std::vector<int>> LBA, int v){
    std::pair<int, std::vector<Edges*>::iterator> edges_containing_x;
    bool check_exist_EC = false;
    for(auto iter = LBA.first.begin(); iter!=LBA.first.end(); iter++){
        if((*iter)->start == v){
            edges_containing_x = std::make_pair((*iter)->end, iter);
            check_exist_EC = true;
            break;
        }
        else if((*iter)->end == v){
            edges_containing_x = std::make_pair((*iter)->start, iter);
            check_exist_EC = true;
            break;
        }
    }
    
    while (check_exist_EC){        
        auto iter = edges_containing_x.second;
        LBA.first.erase(iter);

        LBA = FindEulerPath(LBA, edges_containing_x.first);
        
        check_exist_EC = false;
        for(auto iter = LBA.first.begin(); iter!=LBA.first.end(); iter++){
            if((*iter)->start == v){
                edges_containing_x = std::make_pair((*iter)->end, iter);
                check_exist_EC = true;
                break;
            }
            else if((*iter)->end == v){
                edges_containing_x = std::make_pair((*iter)->start, iter);
                check_exist_EC = true;
                break;
            }
        }
    }
    
    LBA.second.push_back(v);
    return LBA;
}


void Graph_b::Loop_based_algorithm(){
    std::pair<std::vector<Edges*>, std::vector<int>> LBA;
    LBA.first = Graph_to_edges_Euler_check("Loop based algorithm:");
    
    LBA = FindEulerPath(LBA, 5);

    std::cout<<"Loop based algorithm:"<<std::endl;
    for(int i=0; i<LBA.second.size(); i++)
        std::cout<<LBA.second[i]+1<<"  ";
    std::cout<<"\n"<<std::endl;
}

void Graph_b::Kosaraju_algorithm(){
    Type_graph buf = graph;
    graph.clear();
    graph.resize(buf.size());
    for (int i = 0; i < buf.size(); i++){  //G^t
        for(auto iter=buf[i].begin(); iter!=buf[i].end(); iter++){
            Node node; node.add(i, (*iter).get_len());
            graph[(*iter).get_numb()].push_back(node);
        }
    }

    Visit_Stack VS1;
    for (int i = 0; i < buf.size(); i++)
        VS1.visit.push_back(false);

    for (int i = 0; i < graph.size(); i++)
        if(!VS1.visit[i])
            VS1 = dfs_inv(VS1, i);
    
    graph = buf;
    Visit_Stack VS2;
    for (int i = 0; i < graph.size(); i++)
        VS2.visit.push_back(false);

    while (VS1.stack.size()!=0){
        int v = VS1.stack[VS1.stack.size()-1];
        VS1.stack.pop_back();
        if(!VS2.visit[v])
            VS2 = dfs_inv(VS2, v);
    }
    
    std::vector<std::vector<int>> arr = list_to_matrix();
    std::cout<<"Kosaraju's algorithm:"<<std::endl;
    std::cout<<VS2.stack[VS2.stack.size()-1]+1<<"  ";
    for(int i=VS2.stack.size()-2; i>=0; i--){
        if(arr[VS2.stack[i+1]][VS2.stack[i]]==(int)INFINITY)
            std::cout<<"\n";
        std::cout<<VS2.stack[i]+1<<"  ";
    }
    std::cout<<"\n"<<std::endl;
}





void Graph_b::add(int a, int b, int length){push(a, b, length);}
void Graph_b::print_AL(){print_array_list();}
void Graph_b::print_PG(){print_python_graphics("Your graph:");}
void Graph_b::print_AM(){print_adjacency_matrix();}