CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1340;
	title = 134002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 134007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5313101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 134014;
			nextlnk = 101;
			rwdtbl = 134001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5313201;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 4;
				iidx = 837;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 134009;
				ctype = 1;
				idx = 5313101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 134008;
				m1fx = "2778.000000";
				m2fz = "4045.000000";
				m1fy = "0.000000";
				sort = 134005;
				m2widx = 1;
				grade = 132203;
				m0fx = "2739.000000";
				m0ttip = 134015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 134002;
				gtype = 2;
				area = 134001;
				goal = 134004;
				m0fz = "4201.000000";
				m0widx = 1;
				m1ttip = 134016;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "4140.000000";
				m2fx = "2760.000000";
				m2ttip = 134017;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 837;
				cnt0 = 4;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 134008;
			gtype = 2;
			oklnk = 2;
			area = 134001;
			goal = 134004;
			sort = 134005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 134002;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 837;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 837;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 134007;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

