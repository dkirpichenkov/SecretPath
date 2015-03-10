/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  Denis V. Kirpichenkov <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AGENTOPTIONS_H
#define AGENTOPTIONS_H

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

using namespace boost::program_options;
using namespace std;

class AgentOptions
{
public:
  AgentOptions(string filename);    

  bool isClassExcluded(const char *klass);
  bool test(){return false;};
private:
  
  string agentExclude;
  string agentExcludeIgnore;
  string agentInclude;
  string agentIncludeIgnore;
  string appId;
  
  vector<string> excludes;
  vector<string> excludesIgnore;
  
  vector<string> includes;
  vector<string> includesIgnore;
};

#endif // AGENTOPTIONS_H
