CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 970;
	title = 97002;

	CNtlTSGroup
	{
		gid = 0;

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
				eitype = 0;
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
			stdiag = 97007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4151103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 43;
				minlvl = 35;
			}
			CDboTSCheckClrQst
			{
				and = "969;";
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
				conv = 97009;
				ctype = 1;
				idx = 4151103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 97008;
				gtype = 2;
				area = 97001;
				goal = 97004;
				m0fz = "820.000000";
				m0widx = 1;
				sort = 97005;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "2787.000000";
				m0ttip = 97015;
				rwd = 100;
				taid = 1;
				title = 97002;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6011103;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 97014;
			nextlnk = 101;
			rwdtbl = 97001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151103;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 97008;
			gtype = 2;
			oklnk = 2;
			area = 97001;
			goal = 97004;
			sort = 97005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 97002;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

