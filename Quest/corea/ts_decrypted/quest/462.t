CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 462;
	title = 46202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 46209;
				ctype = 1;
				idx = 1654108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 46208;
				gtype = 0;
				area = 46201;
				goal = 46204;
				grade = 132203;
				rwd = 100;
				sort = 46205;
				stype = 2;
				taid = 1;
				title = 46202;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 46214;
			nextlnk = 254;
			rwdtbl = 46201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4261101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 46207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 1654108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 19;
				minlvl = 11;
			}
			CDboTSCheckClrQst
			{
				and = "461;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 46208;
			gtype = 0;
			oklnk = 2;
			area = 46201;
			goal = 46204;
			sort = 46205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 46202;
		}
	}
}

