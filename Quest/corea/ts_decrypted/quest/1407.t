CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1407;
	title = 140702;

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
				conv = 140709;
				ctype = 1;
				idx = 8755301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 140708;
				gtype = 0;
				area = 140701;
				goal = 140704;
				grade = 132203;
				rwd = 100;
				sort = 140705;
				stype = 2;
				taid = 1;
				title = 140702;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 140714;
			nextlnk = 254;
			rwdtbl = 140701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2802101;
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
			cont = 140708;
			gtype = 0;
			oklnk = 2;
			area = 140701;
			goal = 140704;
			sort = 140705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 140702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 140707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8755301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1406;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

