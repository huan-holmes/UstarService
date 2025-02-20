#ifdef INCLUDE_RTKGUI

#include <assert.h>
#include <math.h>
#include <stdlib.h>


#include "rtk.h"

#include "pf.h"
#include "pf_pdf.h"
#include "pf_kdtree.h"


// Draw the statistics
void pf_draw_statistics(pf_t *pf, rtk_fig_t *fig);


// Draw the sample set
void pf_draw_samples(pf_t *pf, rtk_fig_t *fig, int max_samples)
{
  int i;
  double px, py, pa;
  pf_sample_set_t *set;
  pf_sample_t *sample;

  set = pf->sets + pf->current_set;
  max_samples = MIN(max_samples, set->sample_count);

  for (i = 0; i < max_samples; i++)
  {
    sample = set->samples + i;

    px = sample->pose.v[0];
    py = sample->pose.v[1];
    pa = sample->pose.v[2];

    //printf("%f %f\n", px, py);

    rtk_fig_point(fig, px, py);
    rtk_fig_arrow(fig, px, py, pa, 0.1, 0.02);
    //rtk_fig_rectangle(fig, px, py, 0, 0.1, 0.1, 0);
  }

  return;
}


// Draw the hitogram (kd tree)
void pf_draw_hist(pf_t *pf, rtk_fig_t *fig)
{
  pf_sample_set_t *set;

  set = pf->sets + pf->current_set;

  rtk_fig_color(fig, 0.0, 0.0, 1.0);
  pf_kdtree_draw(set->kdtree, fig);

  return;
}


// Draw the CEP statistics
void pf_draw_cep_stats(pf_t *pf, rtk_fig_t *fig)
{
  pf_vector_t mean;
  double var;

  pf_get_cep_stats(pf, &mean, &var);
  var = sqrt(var);

  rtk_fig_color(fig, 0, 0, 1);
  rtk_fig_ellipse(fig, mean.v[0], mean.v[1], mean.v[2], 3 * var, 3 * var, 0);

  return;
}


// Draw the cluster statistics
void pf_draw_cluster_stats(pf_t *pf, rtk_fig_t *fig)
{
  int i;
  pf_cluster_t *cluster;
  pf_sample_set_t *set;
  pf_vector_t mean;
  pf_matrix_t cov;
  pf_matrix_t r, d;
  double weight, o, d1, d2;

  set = pf->sets + pf->current_set;

  for (i = 0; i < set->cluster_count; i++)
  {
    cluster = set->clusters + i;

    weight = cluster->weight;
    mean = cluster->mean;
    cov = cluster->cov;

    // Compute unitary representation S = R D R^T
    pf_matrix_unitary(&r, &d, cov);

    /* Debugging
    printf("mean = \n");
    pf_vector_fprintf(mean, stdout, "%e");
    printf("cov = \n");
    pf_matrix_fprintf(cov, stdout, "%e");
    printf("r = \n");
    pf_matrix_fprintf(r, stdout, "%e");
    printf("d = \n");
    pf_matrix_fprintf(d, stdout, "%e");
    */

    // Compute the orientation of the error ellipse (first eigenvector)
    o = atan2(r.m[1][0], r.m[0][0]);
    d1 = 6 * sqrt(d.m[0][0]);
    d2 = 6 * sqrt(d.m[1][1]);

    if (d1 > 1e-3 && d2 > 1e-3)
    {
      // Draw the error ellipse
      rtk_fig_ellipse(fig, mean.v[0], mean.v[1], o, d1, d2, 0);
      rtk_fig_line_ex(fig, mean.v[0], mean.v[1], o, d1);
      rtk_fig_line_ex(fig, mean.v[0], mean.v[1], o + M_PI / 2, d2);
    }

    // Draw a direction indicator
    rtk_fig_arrow(fig, mean.v[0], mean.v[1], mean.v[2], 0.50, 0.10);
    rtk_fig_arrow(fig, mean.v[0], mean.v[1], mean.v[2] + 3 * sqrt(cov.m[2][2]), 0.50, 0.10);
    rtk_fig_arrow(fig, mean.v[0], mean.v[1], mean.v[2] - 3 * sqrt(cov.m[2][2]), 0.50, 0.10);
  }

  return;
}

#endif
