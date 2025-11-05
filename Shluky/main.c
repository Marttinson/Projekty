/**
 * Kostra programu pro 2. projekt IZP 2022/23
 *
 * Jednoducha shlukova analyza: 2D nejblizsi soused.
 * Single linkage
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    int x; //float mi přišel zbytečný, jednak kvůli absolutní hodnotě, druhak když jsem zkoušel zadat na vstup desetiné číslo do aplikace vykreslující shluky
    // tak nefungovala
    int y; //float
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t*obj;
};

//Struktura, která slouží pro převod textového řetězce (char[]) na celé číslo (int)
struct number_t{
    int* num;
    int size;
    int cap;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);

    // TODO
    c->obj = malloc(sizeof(struct obj_t) * cap);
    c->capacity = cap;
    c->size = 0;
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    // TODO
    free(c->obj);
    c->obj = NULL;
    c->capacity = 0;
    c->size = 0;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
    // TODO
    if(c->size < c->capacity){
        c->obj[c->size].id = obj.id;
        c->obj[c->size].x = obj.x;
        c->obj[c->size++].y = obj.y;
    }
    else{
        c = resize_cluster(c, c->capacity * 2);
        //append_cluster(c, obj);
        c->obj[c->size].id = obj.id;
        c->obj[c->size].x = obj.x;
        c->obj[c->size++].y = obj.y;
    }
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

    // TODO
    for(int i = 0; i < c2->size; i++){
        append_cluster(c1, c2->obj[i]);
    }

    sort_cluster(c1);
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);

    // TODO
    struct cluster_t *o;
    struct cluster_t *prev_o;

    prev_o = &carr[idx + 1];
    for(int i = idx + 1; i < narr; i++){
        o = &carr[i + 1];

        carr[i - 1] = *prev_o;

        prev_o = o;
    }

    carr[narr - 1].size = 0;
    return narr - 1;
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    // TODO
    return sqrtf((powf((float)abs(o1->x - o2->x), 2) + powf((float)abs(o1->y - o2->y), 2)));
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    // TODO
    float min = 10000.0f;
    for(int i = 0; i < c1->size; i++)
        for(int j = 0; j < c2->size; j++) {
            float distance = obj_distance(&c1->obj[i], &c2->obj[j]);
            if (min > distance)
                min = distance;
        }

    return min;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

    // TODO
    float min = 10000.0f;
    for(int i = 0; i < narr; i++){
        for(int j = i + 1; j < narr; j++){
            float distance = cluster_distance(&carr[i], &carr[j]);
            if(min > distance){
                min = distance;
                *c1 = i;
                *c2 = j;
            }
        }
    }
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%d,%d]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

//-------------------------- Number --------------------------
//Funkce a struktura sloužící k převádění z textového řetězce (char[]) na celé číslo (int)

void chars_to_int(int* num, int c, int cont){
    *num += (c - '0') * (int)(pow(10, cont));
}

void init_number(struct number_t *n){
    n->num = malloc(sizeof(int));
    n->size = 0;
    n->cap = 1;
}

void free_number(struct number_t *n){
    free(n->num);
    n->num = NULL;
    n->size = 0;
    n->cap = 0;
}

void resize_number(struct number_t *n, int new_cap){
    n->num = realloc(n->num, sizeof(int) * new_cap);
    n->cap = new_cap;
}

void add_number(struct number_t *n, int c){
    if(n->size < n->cap)
        n->num[n->size++] = c;
    else{
        resize_number(n, n->cap * 2);
        n->num[n->size++] = c;
    }
}

void set_to_zero(struct number_t *n){
    for(int i = 0; i < n->size; i++)
        n->num[i] = 0;
    n->size = 0;
}

int num_to_int(struct number_t *number){
    int n = 0;
    for(int i = 0; i < number->size; i++)
        chars_to_int(&n, number->num[i], number->size - i - 1);

    return n;
}

//------------------------------------------------------------

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t *arr[])
{
    assert(arr != NULL);

    // TODO
    FILE* file = fopen(filename, "r");
    if(!file)
        return 0;

    int c, prev_c = 0;
    int count = 0;
    int i = 0, j = 0, k = 0;

    struct obj_t obj;
    struct number_t id, x, y, co;
    init_number(&id);
    init_number(&x);
    init_number(&y);
    init_number(&co);

    do{
        //Cyklus který načítá data ze souboru
        c = getc(file);

        if(prev_c == '=' || i){
            if(c >= '0' && c <= '9') {
                add_number(&co, c);
                i = 1;
            }
            else {
                i = 0;
                count = num_to_int(&co);
                free_number(&co);

                *arr = malloc(sizeof(struct cluster_t) * count);

                for (int u = 0; u < count; u++)
                    init_cluster(*arr + u, 1);
            }
        }

        if(j){
            if(c >= '0' && c <= '9'){
                switch(k){
                    case 0:
                        add_number(&id, c);
                        break;
                    case 1:
                        add_number(&x, c);
                        break;
                    case 2:
                        add_number(&y, c);
                        break;
                    default:
                        break;
                }
            }
            else if(c == '\n' || c == EOF) {
                k = 0;
                obj.id = num_to_int(&id);
                obj.x = num_to_int(&x);
                obj.y = num_to_int(&y);

                if(obj.id < 0)
                    return -1;
                if(obj.x < 0 || obj.x > 1000)
                    return -1;
                if(obj.y < 0 || obj.y > 1000)
                    return -1;

                append_cluster(*arr + (j - 1), obj);

                set_to_zero(&id);
                set_to_zero(&x);
                set_to_zero(&y);
            }
            else
                k++;
        }

        if(c == '\n')
            j++;

        prev_c = c;
    } while(c != EOF && count != j - 1);

    if(count > j)
        return -1;

    free_number(&id);
    free_number(&x);
    free_number(&y);
    fclose(file);

    return count;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    struct cluster_t *clusters;

    // TODO
    int N;
    int originalCount;

    if(argc == 2)
        N = 1;
    else if (argc == 3){
        struct number_t n;
        init_number(&n);
        int i = 0;
        while (argv[2][i] >= '0' && argv[2][i] <= '9'){
            add_number(&n, argv[2][i++]);
        }
        N = num_to_int(&n);
        free_number(&n);

        if(N < 1){
            fprintf(stderr, "Chyba v zadanem poctu objektu\n");
            return 1;
        }
    }
    else{
        fprintf(stderr, "Chybny format vstupu\n");
        return 1;
    }

    int count = load_clusters(argv[1], &clusters);
    originalCount = count;

    if(!count)
        fprintf(stderr, "Nenalezen soubor\n");
    else if(count == -1)
        fprintf(stderr, "Chyba v vstupnim souboru\n");
    else {
        int indx1, indx2;

        if (count < N)
            fprintf(stderr, "Nelze pozadovat vetsi pocet shluku na vystupu nez je jich na vstupu\n");
        else {
            while (count > N) {
                find_neighbours(clusters, count, &indx1, &indx2);
                for (int j = 0; j < clusters[indx2].size; j++)
                    append_cluster(&clusters[indx1], clusters[indx2].obj[j]);
                count = remove_cluster(clusters, count, indx2);
            }

            for (int i = 0; i < N; i++)
                sort_cluster(&clusters[i]);

            print_clusters(clusters, count);
        }
    }

    for(int i = 0; i < originalCount; i++)
        clear_cluster(&clusters[i]);
    free(clusters);
    return 0;
}