CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1322;
	title = 132202;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 132208;
			gtype = 2;
			oklnk = 2;
			area = 132201;
			goal = 132204;
			sort = 132205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 132202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 132214;
			nextlnk = 101;
			rwdtbl = 132201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372211;
			}
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
			stdiag = 132207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372211;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1320;1321;";
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
				conv = 132209;
				ctype = 1;
				idx = 4372211;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 132208;
				gtype = 2;
				area = 132201;
				goal = 132204;
				m0fz = "4433.000000";
				m0widx = 1;
				sort = 132205;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "2956.000000";
				m0ttip = 132215;
				rwd = 100;
				taid = 1;
				title = 132202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 4263103;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
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

