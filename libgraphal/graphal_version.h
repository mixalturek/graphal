/*
 * Copyright 2013 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRAPHAL_VERSION_H
#define GRAPHAL_VERSION_H


#define VER_HLP(s) #s
#define VER(s) VER_HLP(s)

// See libgraphal/Makefile
#define GRAPHAL_VERSION_MAJOR    1
#define GRAPHAL_VERSION_MINOR    0
#define GRAPHAL_VERSION_REVISION 1

#define GRAPHAL_VERSION VER(GRAPHAL_VERSION_MAJOR) "." VER(GRAPHAL_VERSION_MINOR) "." VER(GRAPHAL_VERSION_REVISION)


#endif // GRAPHAL_VERSION_H
