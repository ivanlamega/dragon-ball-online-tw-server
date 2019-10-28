CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1084;
	title = 108402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
				eitype = 6;
				esctype = 0;
				ectype = -1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 108407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071116;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
			CDboTSCheckClrQst
			{
				and = "1080;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 108408;
			gtype = 2;
			oklnk = 2;
			area = 108401;
			goal = 108404;
			sort = 108405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 108402;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 6;
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
				conv = 108409;
				ctype = 1;
				idx = 4071116;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 108408;
				gtype = 2;
				area = 108401;
				goal = 108404;
				grade = 132203;
				rwd = 100;
				sort = 108405;
				stype = 2;
				taid = 1;
				title = 108402;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActSToCEvt
			{
				dt2 = 108435;
				otype2 = 7;
				widx1 = 4;
				iidx0 = 790;
				otype1 = 7;
				widx2 = 4;
				dt0 = 108433;
				esctype = 0;
				iidx1 = 790;
				it1 = 108431;
				otype0 = 7;
				tidx2 = 17;
				dt1 = 108434;
				etype = 0;
				iidx2 = 790;
				it0 = 108430;
				taid = 1;
				tidx1 = 16;
				widx0 = 4;
				apptype = 0;
				eitype = 6;
				tidx0 = 14;
				ectype = -1;
				it2 = 108432;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 108414;
			nextlnk = 101;
			rwdtbl = 108401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4071116;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 790;
				taid = 1;
				type = 1;
			}
		}
	}
}

