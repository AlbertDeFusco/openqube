/******************************************************************************
  This source file is part of the OpenQube project.

  Copyright 2008-2010 Marcus D. Hanwell
  Copyright 2008 Albert De Fusco
  Copyright 2010 David C. Lonie

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

******************************************************************************/

#ifndef BASISSET_H
#define BASISSET_H

#include "openqubeabi.h"

#include <QtCore/QObject>
#include <QtCore/QFutureWatcher>

namespace openqube
{
  class Cube;

  class OPENQUBE_EXPORT BasisSet : public QObject
  {
    Q_OBJECT

  public:
    /**
     * Constructor.
     */
    BasisSet() : m_electrons(0) {};

    /**
     * Destructor.
     */
    virtual ~BasisSet() {};

    /**
     * Set the number of electrons in the BasisSet.
     * @param n The number of electrons in the BasisSet.
     */
    void setNumElectrons(unsigned int n) { m_electrons = n; }

    /**
     * @return The number of electrons in the molecule.
     */
    unsigned int numElectrons() { return m_electrons; }

    /**
     * @return The number of MOs in the BasisSet.
     */
    virtual unsigned int numMOs() = 0;

    /**
     * Check if the given MO number is the HOMO or not.
     * @param n The MO number.
     * @return True if the given MO number is the HOMO.
     */
    bool HOMO(unsigned int n)
    {
      if (n+1 == static_cast<unsigned int>(m_electrons / 2))
        return true;
      else
        return false;
    }

    /**
     * Check if the given MO number is the LUMO or not.
     * @param n The MO number.
     * @return True if the given MO number is the LUMO.
     */
    bool LUMO(unsigned int n)
    {
      if (n == static_cast<unsigned int>(m_electrons / 2))
        return true;
      else
        return false;
    }

    /**
     * Calculate the MO over the entire range of the supplied Cube.
     * @param cube The cube to write the values of the MO into.
     * @return True if the calculation was successful.
     */
    virtual bool calculateCubeMO(Cube *cube, unsigned int state = 1) = 0;

    /**
     * Calculate the electron density over the entire range of the supplied Cube.
     * @param cube The cube to write the values of the MO into.
     * @return True if the calculation was successful.
     */
    virtual bool calculateCubeDensity(Cube *cube) = 0;

    /**
     * When performing a calculation the QFutureWatcher is useful if you want
     * to update a progress bar.
     */
    virtual QFutureWatcher<void> & watcher()=0;

  protected:
    /// Total number of electrons
    unsigned int m_electrons;

  };

} // End namespace openqube

#endif
