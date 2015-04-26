/* 
 * File:   stringutil.h
 * Author: debdeep
 *
 * Created on 7 March 2015, 1:46 PM
 */

#ifndef STRINGUTIL_H
#define	STRINGUTIL_H

void trim(std::string& str)
{
  //str = "    THIS     ";
  //std::cout << "We are triming " << str << " ...." << std::endl;
  std::string::size_type start_pos = str.find_first_not_of(" ", 0);
  str = str.substr(start_pos, str.size());
  std::string::size_type last_pos = str.find_first_of(" ", 0);
  str = str.substr(0, last_pos);
  //std::cout << "We have trimed " << str << " ...." << std::endl;
}

void tokenize(std::string& str, std::vector<std::string>& tokens, const std::string& delim = " ")
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delim, 0);
  // Find first "non-delimiter".
  std::string::size_type pos     = str.find_first_of(delim, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delim, pos);
    // Find next "non-delimiter"
    pos = str.find_first_of(delim, lastPos);
  }

}

int get_rand_num(int min, int max)
{
  //assert( max > min );
  if( min < max )
    return min + rand()%(max+1-min);

  return min;
}

int get_manhattan_dist(int x1, int y1, int x2, int y2 )
{
  return (abs(x1 - x2) + abs( y1- y2) );
}

#endif	/* STRINGUTIL_H */

