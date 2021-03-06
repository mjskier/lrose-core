/* 	$Id: Pdata.h,v 1.1 2007/09/22 21:08:21 dixon Exp $	 */

# ifndef INCPdatah
# define INCPdatah

struct paramdata_d {
    char pdata_desc[4];	      /* parameter data descriptor identifier: ASCII */
			      /* characters "RDAT" stand for sweep info */
			      /* block Descriptor. */
    si32  pdata_length;       /* parameter data descriptor length in bytes. */
    char  pdata_name[8];      /*name of parameter*/
}; /* End of Structure */



typedef struct paramdata_d paramdata_d;
typedef struct paramdata_d PARAMDATA;

# endif /* INCPdatah */
