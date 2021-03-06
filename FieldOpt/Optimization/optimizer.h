/******************************************************************************
 *
 *
 *
 * Created: 04.12.2015 2015 by einar
 *
 * This file is part of the FieldOpt project.
 *
 * Copyright (C) 2015-2015 Einar J.M. Baumann <einar.baumann@ntnu.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *****************************************************************************/

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Utilities/settings/optimizer.h"
#include "case.h"
#include "case_handler.h"
#include "constraints/constraint_handler.h"
#include "optimization_exceptions.h"
#include "Model/properties/variable_property_container.h"

namespace Optimization {

/*!
 * \brief The Optimizer class is the abstract parent class for all optimizers. It is primarily
 * designed to support direct search optimization algorithms.
 */
class Optimizer
{
public:
    Optimizer() = delete;

    /*!
     * \brief GetCaseForEvaluation Get a new, unevaluated case for evaluation.
     *
     * If no unevaluated cases are currently available in the CaseHandler, the iterate()
     * method is called to generate new cases.
     * \return Pointer to a new, unevaluated case.
     */
    Case *GetCaseForEvaluation();

    /*!
     * \brief SubmitEvaluatedCase Submit an already evaluated case to the optimizer.
     *
     * The submitted case is marked as recently evaluated in the CaseHandler.
     * \param c Case to submit.
     */
    void SubmitEvaluatedCase(Case *c);

    /*!
     * \brief GetTentativeBestCase Get the best case found so far.
     * \return
     */
    Case *GetTentativeBestCase() const;

    /*!
     * \brief case_handler Get the case handler. Used by the bookkeeper in the runner lib.
     */
    CaseHandler *case_handler() const { return case_handler_; }

    // Status related methods
    int nr_evaluated_cases() const { return case_handler_->EvaluatedCases().size(); }
    int nr_queued_cases() const { return case_handler_->QueuedCases().size(); }
    int nr_recently_evaluated_cases() const { return case_handler_->RecentlyEvaluatedCases().size(); }

    /*!
     * \brief IsFinished Check whether the optimization is finished, i.e. if the the optimizer has
     * reached some  termination condition.
     *
     * This method should be called before attempting to get a new case for evaluation.
     * \return True if the optimizer has finished, otherwise false.
     */
    virtual bool IsFinished() = 0;

    virtual QString GetStatusStringHeader() const; //!< Get the CSV header for the status string.
    virtual QString GetStatusString() const; //!< Get a CSV string describing the current state of the optimizer.

protected:
    /*!
     * \brief Optimizer
     * \param settings Settings for the optimizer.
     * \param base_case The base case for optimizer. Must already have been evaluated (i.e. have an objective function value).
     */
    Optimizer(::Utilities::Settings::Optimizer *settings, Case *base_case, ::Model::Properties::VariablePropertyContainer *variables);

    /*!
     * \brief BetterCaseFoundLastEvaluation Searches the list of recently evaluated cases in the case handler for a case
     * with a better objective function value than the current tentative best case.
     * \return True if a better case is found, otherwise false.
     */
    bool betterCaseFoundLastEvaluation();

    /*!
     * \brief ApplyNewTentativeBestCase Sets the tentative best case to the best case found in the case handler (if one is found).
     */
    void applyNewTentativeBestCase();

    /*!
     * \brief iterate Performs an iteration, generating new cases and adding them to the case_handler.
     */
    virtual void iterate() = 0;

    Case *tentative_best_case_; //!< The best case encountered thus far.
    CaseHandler *case_handler_; //!< All cases (base case, unevaluated cases and evaluated cases) passed to or generated by the optimizer.
    Constraints::ConstraintHandler *constraint_handler_; //!< All constraints defined for the optimization.
    int max_evaluations_; //!< Maximum number of objective function evaluations allowed before terminating.
    int iteration_; //!< The current iteration.
    ::Utilities::Settings::Optimizer::OptimizerMode mode_; //!< The optimization mode, i.e. whether the objective function should be maximized or minimized.
};

}

#endif // OPTIMIZER_H
